#include <cstring>
#include <iostream>

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <ip-address> <port>" << std::endl;
        return 1;
    }

    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cerr << "Winsock initialization failed" << std::endl;
        return 1;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET)
    {
        std::cerr << "Failed to create a socket" << std::endl;
        return 1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    if (connect(client_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to connect with the server" << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    char buffer[1001]{0};
    switch (recv(client_socket, buffer, 1000, 0))
    {
    case -1:
        std::cerr << "Failed to receive a message" << std::endl;
        break;
    case 0:
        std::cerr << "Failed to receive a message" << std::endl;
        break;
    default:
        std::cout << buffer << std::endl;
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}

#else

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <ip-address> <port>" << std::endl;
        return 1;
    }

    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "Failed to create a socket" << std::endl;
        return 1;
    }

    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Failed to connect with the server" << std::endl;
        close(client_socket);
        return 1;
    }

    char buffer[1001]{0};
    switch (recv(client_socket, buffer, 1000, 0))
    {
    case -1:
        std::cerr << "Failed to receive a message" << std::endl;
        break;
    case 0:
        std::cerr << "Server disconnected" << std::endl;
        break;
    default:
        std::cout << "Message from server: " <<  buffer << std::endl;
    }

    close(client_socket);
    return 0;
}

#endif
