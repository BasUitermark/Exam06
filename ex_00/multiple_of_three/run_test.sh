#!/bin/bash

gcc test_multi_of_3.c -o test_multi_of_3 -Wall

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
    "24"
    "25"
)

declare -a expected_outputs=(
    "0"  # 0 is a multiple of 3
    "3"  # Next multiple of 3 after 1
    "3"  # Next multiple of 3 after 2
    "3"  # 3 is a multiple of 3
    "6"  # Next multiple of 3 after 4
    "6"  # Next multiple of 3 after 5
    "6"  # 6 is a multiple of 3
    "24" # 24 is a multiple of 3
    "27" # Next multiple of 3 after 25
)

# Run test cases
for i in "${!test_cases[@]}"; do
    output=$(./test_multi_of_3 ${test_cases[i]})
    print_result $((i+1)) "${test_cases[i]}" "$output" "${expected_outputs[i]}"
done
