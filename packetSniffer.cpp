#include <iostream>
#include <pcap.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <cstring>
#include <limits>

/* check if code is being compiled in macOS, if so define the MACOS macro for platform-specific operations */
#ifdef __APPLE__
#define MACOS
#endif

int main(int argc, char* argv[]) {

    
    char* dev;

    /* check if there are at least two arguments (program name and one additional argument) */
    if (argc >= 2) {
        /* 
         * we will access command line arguments below using the
         * argv array which holds argument separated by spaces 
         */
        std::cout << "Program name : " << argv[0] << std::endl;
        std::cout << "Device Name  : " << argv[1] << std::endl;
        
        /* we assign the device name to the device variable */
        dev = argv[1];
        
    return 0;
}