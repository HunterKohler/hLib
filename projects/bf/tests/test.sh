#!/bin/zsh

function message {
    left=$(( (29 - ${#1}) / 2 ))
    right=$(( (30 - ${#1}) / 2 ))
    codes=$(echo ${@[@]:2} | tr " " ";")
    printf "\e["$codes"m%"$left"s"$1"%"$right"s\e[0m\n"
}

message "Compiling..." 100
return=$($CC -fdiagnostics-color=always ./src/bf.c -o ./build/bf 2>&1)

if [[ -z $return ]]; then
    message "Compiled" 100 32
    echo
else
    echo >&2 $return
    message >&2 "Could not compile" 100 31
    exit 1
fi

# $1 - testname
# $2 - filename
# $3 - input
# $4 - expected ouput
function testcase {
    output=$(./build/bf $2 <<< $3)

    if [[ $output == $4 ]] ; then
        echo "test: \e[32m$1\e[0m"
    else
        echo "test: \e[31m$1\e[0m"
        echo "    expected: \"$4\""
        echo "    recieved: \"$output\""
    fi
}

message "Running tests..." 100

testcase "verbose print \"a\"" "./tests/a.b" "" "a"
testcase "looping print \"a\"" "./tests/loop_a.b" "" "a"
testcase "add inputs" "./tests/add.b" "!&" "G"
testcase "Hello World!" "./tests/hello_world.b" "" "Hello World!"