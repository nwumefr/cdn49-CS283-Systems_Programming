#!/bin/bash

# Set the port for the server
DSH_PORT="6568"  # Change this if needed
LOG_FILE="dsh_server.log"

# Kill any existing `dsh` server on the same port
echo "Stopping any existing dsh server on port $DSH_PORT..."
pkill -f "dsh -s -p $DSH_PORT"

# Start the dsh server in the background
echo "Starting dsh server on port $DSH_PORT..."
./dsh -s -i 0.0.0.0 -p $DSH_PORT &

# Wait for a moment to allow the server to start
sleep 2

# Check if the server is running
echo "Checking if server is listening on port $DSH_PORT..."
ss -tulnp | grep $DSH_PORT 


echo "DSH server started. Logs available in $LOG_FILE."

# # # Start the dsh server in the background
# echo "Starting dsh client"
# ./dsh -c -i 129.25.203.107 -p $DSH_PORT 
