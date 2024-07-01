#!/bin/bash

DIRECTORY="tests"
PROGRAM="./mtll"

# Test case score
SUCCESS=0
TOTAL=0

# Program Existance
if [ ! -f "$PROGRAM" ]; then
    echo "Program $PROGRAM not found. Compile first."
    exit 1
fi

# Directory Existance
if [ ! -d "$DIRECTORY" ]; then
    echo "Test directory $DIRECTORY not found."
    exit 1
fi

echo " Part 1 and 2 Testcases "

run_test_case() {

    local testcase=$1

    $PROGRAM < "$DIRECTORY/${testcase}.in" > "$DIRECTORY/${testcase}.out"
    
    if diff -u "$DIRECTORY/${testcase}.out" "$DIRECTORY/${testcase}.expected"; then
        echo "Test case: $testcase SUCCESS"
        ((SUCCESS++))
    else
        echo "Test case: $testcase FAILED"
    fi
    ((TOTAL++))
}

# Part 1 Test Case -> Mixture of positive and negative inputs
run_test_case "part1"

# Part 2 Testcase -> Mixture of positive and negative inputs
run_test_case "part2"

# Edge Case 1
run_test_case "edge1"

# Edge Case 2
run_test_case "edge2"

# Edge Case 3
run_test_case "edge3"

echo "$SUCCESS out of $TOTAL tests passed."


# Part 3 Testcases
echo "Part 3 Test Cases"

run_test_case2() {

    local testcase=$1

    $PROGRAM < "$DIRECTORY/${testcase}.in" > "$DIRECTORY/${testcase}.out"
    
    if diff -u "$DIRECTORY/${testcase}.out" "$DIRECTORY/${testcase}.expected"; then
        echo "Test case: $testcase SUCCESS"
        ((SUCCESS++))
    else
        echo "Test case: $testcase FAILED"
    fi
    ((TOTAL++))
}

# Part 3 Test Case -> Mixture of positive inputs
run_test_case2 "part3"

# Edge Case 4
run_test_case2 "edge4"