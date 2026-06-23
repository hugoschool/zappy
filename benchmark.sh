#!/bin/bash

filename="benchmark_output"
echo -e "\n\e[1;33mBenchmark tester Start\e[0;37m\n"

if [[ $1 == "--help" ]]; then
    echo -e "Usage:\t./benchmark.sh [nb_iter] [server_path] [ia_path]"
    exit 0
fi

ai_thread() {
    ./$1 -p 4242 -n freaky > /dev/null
    return
}

server_thread() {
    (sleep 6 ; echo "/quit") | ./$1 -p 4242 -x 30 -y 30 -n freaky tuff -c 1 -f 1000 > /tmp/$filename
    return
}

for i in $(seq 1 $1); do
    echo -e "Iteration $i"
    server_thread $2 &
    ai_thread $3

    #echo -e "Start reading"
    #while read -r line; do
    #    echo -e "line :$line"
    #done < "$filename"
done
