#!/usr/bin/env bats

SERVER_PORT=7890  # Change this if needed
SERVER_PID=""
SERVER_PREFACE="socket client mode:  addr:127.0.0.1:7890Attempting to connect at 127.0.0.1:7890Connected to server at 127.0.0.1:7890dsh4> "
SERVER_SUFFIX="dsh4> cmd loop returned 0"
setup() {
    # Start the server in the background
    ./dsh -s -i 0.0.0.0 -p $SERVER_PORT > server.log 2>&1 &
    SERVER_PID=$!
    sleep 1  # Give the server time to start
}

teardown() {
    # Stop the server after each test
    if [ -n "$SERVER_PID" ]; then
        kill $SERVER_PID
        wait $SERVER_PID 2>/dev/null
    fi
}

@test "Basic Command Execution" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
echo "Hello, world!"
EOF

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"

    [ "$status" -eq 0 ]
    [[ "$output" == *"Hello, world!"* ]]
}

@test "List Directory Contents" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
ls
EOF

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"

    [ "$status" -eq 0 ]
    [[ "$output" != "" ]]  # Ensure it lists the test file
}

@test "Pipeline Command Execution" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
ls | grep .c
EOF

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"

    [ "$status" -eq 0 ]
    [[ "$output" != "" ]]
}

@test "Pipe with wc" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
echo -e "line1\nline2\nline3" | wc -l
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "3" ]]
}

@test "Pipe with cat and grep" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
echo -e "alpha\nbeta\ngamma" | grep beta
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "beta" ]]
}


@test "Pipe with multiple greps" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
echo -e "foo\nbar\nbaz" | grep ba | grep z
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "baz" ]]
}

@test "Pipe with sort and uniq" {
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
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
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
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
    run ./dsh -c -i 127.0.0.1 -p $SERVER_PORT <<EOF
echo -e "line1\nline2\nline3\nline4" | tail -n 2
EOF
    
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    
    [ "$status" -eq 0 ]
    [[ "$output" =~ "line4" ]]
}
