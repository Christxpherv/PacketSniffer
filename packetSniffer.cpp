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