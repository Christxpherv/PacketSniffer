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

/* 
 * create the packet_handler function that handles all the data
 * parses the packet headers, extracts source and destination information, 
 * and prints hexadecimal and ASCII representations of the packet data.
 */
void packet_handler(unsigned char* user_data, const struct pcap_pkthdr* pkthdr, const unsigned char* packet_data) {
    /* lets the user know where the start of a packet is located */
    std::cout << "----------------- Packet Data Captured -----------------" << std::endl;
    /* lets the user know the length of the packet */
    std::cout << "Captured Packet Length: " << pkthdr->len << " bytes." << std::endl;
}

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

        struct ifaddrs* ifap;
        struct sockaddr_in* addr;

        /* 
         * below we are checking that we can acquire our local IP
         * address and if we are successful we print it so we can 
         * compare across packets if needed.
         */
        if (getifaddrs(&ifap) == 0) {
            for (struct ifaddrs* ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET) {
                    addr = (struct sockaddr_in*)ifa->ifa_addr;

                    /* 
                     * ese "en0" for Ethernet/Wi-Fi interface 
                     * note: this is assigned by argv[1] 
                     */
                    if (strcmp(ifa->ifa_name, dev) == 0) {
                        std::cout << "Your IP address on " << ifa->ifa_name << ": " << inet_ntoa(addr->sin_addr) << std::endl;
                    }
                }
            }

            /* Free the memory allocated by getifaddrs */
            freeifaddrs(ifap); 
        } 
        
        else {
            std::cerr << "Failed to get IP address." << std::endl;
        }

    } else {

        std::cout << "No additional command-line arguments provided." << std::endl;
    }

    /* create an error buffer to store any errors that may be thrown and set the buffer to max size */
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle;

    /* 
     * find all available network devices 
     * note: we do not use the alldevs in this
     * program, and is only here for reference.
     * alldevs contains all devices on the system
     * and can access each by walking the list
     */
    pcap_if_t* alldevs;
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding network devices: " << errbuf << std::endl;
        return 1;
    }

    /* sets the actual device that we are going to be listening to */
    pcap_if_t* device;
    int deviceCount = 0;

    /* specifies promiscuous mode - meaning all network traffic is captured (live listen) */
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Could not open device " << dev << ": " << errbuf << std::endl;
        
        /* free all devices in the list including that stored in dev */
        pcap_freealldevs(alldevs);
        return 1;
    }

    /* start capturing packets and call the packet_handler function for each packet */ 
    pcap_loop(handle, 0, packet_handler, nullptr);

    /* close the capture handle when done */ 
    pcap_close(handle);

    /* free the device list */
    pcap_freealldevs(alldevs);

    return 0;

}