#include <iostream>

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

int main()
{
    // todo: implement
    std::cout << "Hello, Windows" << std::endl;
}

#else

#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    // short and long conversions
    unsigned short host_port = 0x1234;
    unsigned short network_port = 0x0;
    unsigned long host_address = 0x01020304;
    unsigned long network_address = 0x0;

    network_port = htons(host_port);
    network_address = htonl(host_address);

    printf("Host ordered port: %#06x \n", host_port);
    printf("Network ordered port: %#06x \n", network_port);
    printf("Host ordered address: %#010lx \n", host_address);
    printf("Network ordered address: %#010lx \n", network_address);

    // network to address
    sockaddr_in address;
    address.sin_addr.s_addr = network_address;
    char* network_address_text = inet_ntoa(address.sin_addr);
    if (network_address_text)
    {
        std::cout << "Network address: " << network_address_text << std::endl;
    }

    // address to network
    if (inet_aton("5.6.7.8", &address.sin_addr))
    {
        printf("Network ordered address: %#010lx \n", (unsigned long)address.sin_addr.s_addr);
    }
}

#endif
