#!/bin/bash

gcc test_fprime.c -o test_fprime -Wall

# ANSI color codes
BOLD='\033[1m'
RED='\033[0;31m\033[1m'
GREEN='\033[0;32m\033[1m'
NO_COLOR='\033[0m'

print_result() {
    local test_num=$1
    local desc=$2
    local output=$(echo "$3" | xargs)
    local expected=$(echo "$4" | xargs)

    echo -ne "${BOLD}Test #$test_num ($desc): ${NO_COLOR}"
    if [ "$output" == "$expected" ]; then
        echo -e "${GREEN}Correct${NO_COLOR}"
    else
        echo -e "${RED}Incorrect${NO_COLOR}"
        echo -e "${BOLD}Output:${NO_COLOR} $output   ${BOLD}Expected:${NO_COLOR} $expected"
    fi
    echo -e ""
}

# Define test cases (number to factor) and expected outputs (factorization result)
declare -a test_cases=(
    "1"
    "2"
    "3"
    "4"
    "5"
    "6"
    "7"
    "8"
    "9"
    "10"
    "25"
    "42"
    "100"
)

declare -a expected_outputs=(
    "1"
    "2"
    "3"
    "2*2"
    "5"
    "2*3"
    "7"
    "2*2*2"
    "3*3"
    "2*5"
    "5*5"
    "2*3*7"
    "2*2*5*5"
)

# Run test cases
for i in "${!test_cases[@]}"; do
    output=$(./test_fprime ${test_cases[i]})
    print_result $((i+1)) "${test_cases[i]}" "$output" "${expected_outputs[i]}"
done
