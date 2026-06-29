#!/bin/bash


filename="/tmp/benchmark_output"
framerate=1000
port=4242
sleep=7

if [[ $# != 4 && $# != 3 || $1 == "--help" ]]; then
    echo -e "Usage:\t./benchmark.sh [nb_iter] [server_path] [ia_path] ([-t])"
    exit 0
fi

echo -e "\n\e[1;33mBenchmark tester Start\e[0;37m\n"

if [[ $4 == "-t" ]]; then
    sleep=33
    framerate=100
fi

ai_thread() {
    ./$1 -p $port -n freaky 1> /dev/null
    return
}

server_thread() {
    (sleep $sleep ; echo "/quit") | ./$1 -p $port -x 30 -y 30 -n freaky -c 1 -f "$framerate" > "$filename$2"
    return
}
pid_array=()
for i in $(seq 1 $1); do
    echo -e "Iteration $i"
    server_thread $2 $i &
    pid_server=$!

    ai_thread $3 &
    port=$((port + 2))
    pid_array+=($pid_server)
done

for element in "${pid_array[@]}"; do
    wait "$element"
done
echo ""

results=()

for i in $(seq 1 $1); do
    while read -r line; do
        if [[ $line == "Server shutting down." ]]; then
            break
        fi
        if [[ $line == "The game ended in"* ]]; then
            echo -e "$filename$i:"
            if [[ "$line" =~ ([0-9]+).*[^0-9]([0-9]+) ]]; then
                echo -e "\e[1;37mFinish in: ${BASH_REMATCH[1]},${BASH_REMATCH[2]}\e[0;37m sec\n"
                results+=("${BASH_REMATCH[1]}.${BASH_REMATCH[2]}")
            fi
        fi
    done < "$filename$i"
    finish+=("$i")
done

echo -e "\n\e[1;32mResults:\e[0;37m\n"

echo -e "$((${#results[@]}))/$1 test passed.\n"
results=($(printf '%s\n' "${results[@]}"|sort))
sum=$(IFS="+"; bc <<< "${results[*]}")
avrg=$(echo "scale=6; $sum / ${#results[@]}" | bc -l)
echo -e "Average: \e[1;37m${avrg}s\e[0;37m"
echo -e "Fastest: \e[1;37m${results[0]}s\e[0;37m\tSlowest: \e[1;37m${results[-1]}s\e[0;37m"
