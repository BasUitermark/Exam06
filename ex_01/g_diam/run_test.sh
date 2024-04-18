#!/bin/bash

# Compile the C program
gcc g_diam.c -o graph_diameter -Wall -Werror -Wextra

# ANSI color codes for formatting output
BOLD='\033[1m'
RED='\033[0;31m\033[1m'
GREEN='\033[0;32m\033[1m'
NO_COLOR='\033[0m'

print_result() {
    local test_num=$1
    local desc=$2
    local output="$3"
    local expected="$4"

    echo -ne "${BOLD}Test #$test_num ($desc): ${NO_COLOR}"
    if [ "$output" == "$expected" ]; then
        echo -e "${GREEN}Correct${NO_COLOR}"
    else
        echo -e "${RED}Incorrect${NO_COLOR}"
        echo -e "${BOLD}Output:${NO_COLOR} $output   ${BOLD}Expected:${NO_COLOR} $expected"
    fi
    echo -e ""
}

# Define tests
declare -a tests=(
    "17-5 5-8 8-2 2-8 2-8 17-21 21-2 5-2 2-6 6-14 6-12 12-19 19-14 14-42"
    "1-2 2-3 4-5 5-6 6-7 7-8 9-13 13-10 10-2 10-11 11-12 12-8 16-4 16-11 21-8 21-12 18-10 18-13 21-18"
    "0-1 1-2 2-0 3-4 4-3"
    "0-1 1-2 2-3 3-4 4-0"
    "0-1 1-2 2-3"
    "0-1 1-2 2-3 3-4 4-5 5-6"
    "0-1 1-2 2-0 3-4 4-5 5-3" 
    "0-1 2-3 4-5"
    "0-1 1-2 2-0 3-4 4-5 5-3 0-3"
    "invalid input"
    "0-1 1-2 two-3 3-4"
)

declare -a expected_outputs=(
	"10"
	"15"
	"3"
	"5"
	""
	"6"
	"3"
	""
	"6"
	"1"
	"5"
)

# Loop through tests
for i in "${!tests[@]}"; do
    # Correctly pass the entire string as one argument
    output=$(./graph_diameter "${tests[i]}")
    print_result $((i+1)) "Test Case $((i+1))" "$output" "${expected_outputs[i]}"
done