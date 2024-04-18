#!/bin/bash

# Compile the C program
gcc islands.c -o map_analysis -Wall -Werror -Wextra

# ANSI color codes for formatting output
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
	"maps/non_exist.txt"
	"maps/readable_file.txt"
    "maps/test_map0.txt"
    "maps/test_map1.txt"
    "maps/test_map2.txt"
    "maps/test_map3.txt"
    "maps/test_map4.txt"
    "maps/test_map5.txt"
    "maps/test_map6.txt"
    "maps/test_map7.txt"
    "maps/test_map8.txt"
    "maps/test_map9.txt"
    "maps/test_map10.txt"
    "maps/test_map11.txt"
    "maps/test_map12.txt"
    "maps/test_map13.txt"
    "maps/test_map14.txt"
    "maps/test_map15.txt"
)

declare -a expected_outputs=(
	"Error opening file"
	"Error reading file"
	"0"
    "3"
    "3"
    "16"
    "Invalid Map"
    "Invalid Map"
    "4"
    "64"
    "8"
    "Invalid Map"
    "Invalid Map"
    "72"
    "1"
    "4"
    "Invalid Map"
    "Invalid Map"
)

# Run test cases
for i in "${!test_cases[@]}"; do
    output=$(./map_analysis "${test_cases[i]}" 2>&1)
    print_result $((i+1)) "${test_cases[i]}" "$output" "${expected_outputs[i]}"
done
