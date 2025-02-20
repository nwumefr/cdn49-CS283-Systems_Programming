#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF
    stripped_output=$(echo "$output")
    ls_output=$(ls)
    expected_output="${ls_output}"$'\ndsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "check ls -a runs without errors" {
    run ./dsh <<EOF                
ls -a
EOF
    stripped_output=$(echo "$output")
    ls_output=$(ls -a)
    expected_output="${ls_output}"$'\ndsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "cd with no args has no output" {
    run ./dsh <<EOF                
cd
EOF
    stripped_output=$(echo "$output")
    expected_output='dsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "cd with no args does not change pwd" {
    run ./dsh <<EOF                
cd
pwd
EOF
    stripped_output=$(echo "$output")
    pwd_output=$(pwd)
    expected_output="${pwd_output}"$'\ndsh2> dsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "cheking if cd with one arg changes pwd" {
    dirT='test'
    if [ -e "$dirT" ];then rmdir "$dirT" ; fi 
    run ./dsh <<EOF 
mkdir test               
cd test
pwd
EOF
    stripped_output=$(echo "$output")
    pwd_output=$(pwd)
    expected_output="${pwd_output}/test"$'\ndsh2> dsh2> dsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "testing if mkdir creates directory" {
    dirT='test'
    if [ -e "$dirT" ];then rmdir "$dirT" ; fi 
    run ./dsh <<EOF 
mkdir test               
ls
EOF
    stripped_output=$(echo "$output")
    pwd_output=$(ls)
    expected_output="${pwd_output}"$'\ndsh2> dsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "testing if rmdir deletes directory" {
    dirT='test'
    if [ -e "$dirT" ];then rmdir "$dirT" ; fi 
    run ./dsh <<EOF 
mkdir test               
rmdir test
ls
EOF
    stripped_output=$(echo "$output")
    pwd_output=$(ls)
    expected_output="${pwd_output}"$'\ndsh2> dsh2> dsh2> dsh2> cmd loop returned 0'

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}
