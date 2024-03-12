# Packet Sniffer

## Code Description

This C++ program utilizes the pcap library to capture and analyze network packets. It distinguishes
between macOS and Linux platforms, parsing Ethernet headers on Linux and directly handling IP and
TCP headers on macOS. The code extracts and prints information such as MAC addresses, IP addresses,
and port numbers. It also displays hexadecimal and ASCII representations of the captured packet
data. The program allows users to specify a network interface, retrieves the local IP address of
the interface, and continuously captures and analyzes network packets until manually terminated.

## How to Run the Code

### Step One: Compile the Code

Open your laptop's terminal and run the following command to compile the code:

run % g++ -o packetSniffer packetSniffer.cpp -lpcap  
format: g++ -o \<name\> \<fileName\> -lpcap  
explanation: In C++, the g++ -o command is used to specify the output filename, and the -lpcap line is used to link the external library.

### Step Two: Use Sudo
run % sudo ./packetSniffer en0  
format: sudo ./packetSniffer \<deviceName\>