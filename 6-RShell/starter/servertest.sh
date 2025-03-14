#start the server on tux, use port 7890
./dsh -s -i 0.0.0.0 -p $1 &
disown
#start the client to connect to tux, assuming tux's IP
#address is 129.25.203.107 and the server is running
#on port number 7890
./dsh -c -i 127.0.0.1 -p $1