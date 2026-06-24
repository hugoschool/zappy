#!/bin/bash


filename="/tmp/benchmark_output"
framerate=1000
echo -e "\n\e[1;33mBenchmark tester Start\e[0;37m\n"

if [[ $# != 3|| $1 == "--help" ]]; then
    echo -e "Usage:\t./benchmark.sh [nb_iter] [server_path] [ia_path]"
    exit 0
fi

ai_thread() {
    ./$1 -p 4242 -n freaky 1> /dev/null
    return
}

server_thread() {
    (sleep 5 ; echo "/quit") | ./$1 -p 4242 -x 30 -y 30 -n freaky tuff -c 1 -f "$framerate" > "$filename$2"
    return
}

for i in $(seq 1 $1); do
    echo -e "Iteration $i"
    server_thread $2 $i &
    pid_server=$!

    ai_thread $3 &

    wait $pid_server
done

echo ""

results=()

for i in $(seq 1 $1); do
    idx_line=0
    while read -r line; do
        if [[ $line == "Server shutting down." ]]; then
            break
        fi
        if [ $idx_line == 17 ]; then
            echo -e "$filename$i:"
            if [[ "$line" =~ ([0-9]+).*[^0-9]([0-9]+) ]]; then
                echo -e "\e[1;37mFinish in: ${BASH_REMATCH[1]},${BASH_REMATCH[2]}\e[0;37m sec\n"
                results+=("${BASH_REMATCH[1]}.${BASH_REMATCH[2]}")
            fi
        fi
        ((idx_line+=1))
    done < "$filename$i"
    finish+=("$i")
done

echo -e "\n\e[1;32mResults:\e[0;37m\n"
echo -e "$results"
