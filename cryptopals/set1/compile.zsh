#!/bin/zsh

mkdir bin &>/dev/null
for i in $(find src/** -type d) ; do
    mkdir -p bin/${i#src/} &>/dev/null
done

for i in $(find src/**.cpp -type f) ; do
    echo $i
    g++ $i -std=c++11 -o bin/${"${i#*/}"%.cpp}
done
