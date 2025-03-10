#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Basic Pipe Execution" {
    run "./dsh" <<EOF
ls | grep .c
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
}

@test "Pipe with wc" {
    run "./dsh" <<EOF
echo -e "line1\nline2\nline3" | wc -l
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "3" ]]
}

@test "Pipe with cat and grep" {
    run "./dsh" <<EOF
echo -e "alpha\nbeta\ngamma" | grep beta
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "beta" ]]
}


@test "Pipe with multiple greps" {
    run "./dsh" <<EOF
echo -e "foo\nbar\nbaz" | grep ba | grep z
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "baz" ]]
}

@test "Pipe with sort and uniq" {
    run "./dsh" <<EOF
echo -e "apple\nbanana\napple\ncherry" | sort | uniq
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "apple" ]]
    [[ "$output" =~ "banana" ]]
    [[ "$output" =~ "cherry" ]]
}

@test "Pipe with head command" {
    run "./dsh" <<EOF
echo -e "line1\nline2\nline3\nline4" | head -n 2
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "line1" ]]
    [[ "$output" =~ "line2" ]]
}

@test "Pipe with tail command" {
    run "./dsh" <<EOF
echo -e "line1\nline2\nline3\nline4" | tail -n 2
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "line4" ]]
}

