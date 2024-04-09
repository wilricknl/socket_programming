#include <iostream>

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

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

    // network to address with inet
    {
        sockaddr_in address;
        address.sin_addr.s_addr = network_address;
        char* network_address_text = inet_ntoa(address.sin_addr);
        if (network_address_text)
        {
            std::cout << "Network address: " << network_address_text << std::endl;
        }
    }

    // address to network with inet
    {
        if (auto address = inet_addr("5.6.7.8"))
        {
            printf("Network ordered address: %#10lx \n", address);
        }
    }

    // network to address with Windows
    {
        char* string_address = "01.02.03.04:80";

        sockaddr_in address;
        int address_size = sizeof(address);
        WSAStringToAddress(string_address, AF_INET, NULL, (SOCKADDR*)&address, &address_size);

        printf("WSAStringToAddress: %#010lx:%#6x\n", address.sin_addr, address.sin_port);
    }

    // address to network with Windows
    {
        sockaddr_in address;
        address.sin_addr.s_addr = htonl(0x01020304);
        address.sin_port = htons(80);
        address.sin_family = AF_INET;
        int address_size = sizeof(address);

        // Important to have the sin_family set, otherwise this function will fail.
        char buffer[50]{0};
        DWORD buffer_size = sizeof(buffer);
        WSAAddressToString((sockaddr*)&address, address_size, NULL, buffer, &buffer_size);

        printf("WSAAddressToString: %s\n", buffer);
    }

    WSACleanup();
    return 0;
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
