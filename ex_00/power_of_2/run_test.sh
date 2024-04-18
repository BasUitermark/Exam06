#!/bin/bash

gcc test_pow_of_2.c -o test_pow_of_2 -Wall

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

# Define test cases and expected outputs
declare -a test_cases=(
    "0"
    "1"
    "2"
    "3"
    "4"
    "5"
    "6"
    "8"
    "16"
    "31"
    "32"
    "64"
    "127"
    "128"
    "256"
)

declare -a expected_outputs=(
    "0"  # 0 is not a power of 2
    "1"  # 1 is 2^0
    "1"  # 2 is 2^1
    "0"  # 3 is not a power of 2
    "1"  # 4 is 2^2
    "0"  # 5 is not a power of 2
    "0"  # 6 is not a power of 2
    "1"  # 8 is 2^3
    "1"  # 16 is 2^4
    "0"  # 31 is not a power of 2
    "1"  # 32 is 2^5
    "1"  # 64 is 2^6
    "0"  # 127 is not a power of 2
    "1"  # 128 is 2^7
    "1"  # 256 is 2^8
)

# Run test cases
for i in "${!test_cases[@]}"; do
    output=$(./test_pow_of_2 ${test_cases[i]})
    print_result $((i+1)) "${test_cases[i]}" "$output" "${expected_outputs[i]}"
done
