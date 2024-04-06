#include <iostream>

#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cerr << "Winsock initialization failed" << std::endl;
    }

    SOCKET server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        std::cerr << "Failed to create a socket" << std::endl;
    }

    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[1]));

    if (bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to bind the server" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 5) == SOCKET_ERROR)
    {
        std::cerr << "Failed to start listening" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    sockaddr_in client_address;
    int client_address_size = sizeof(client_address);
    SOCKET client_socket = accept(server_socket, (SOCKADDR*)&client_address, &client_address_size);
    if (client_socket == INVALID_SOCKET)
    {
        std::cout << "Failed to accept client socket" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    char message[] = "Hello, from a Windows socket!";
    send(client_socket, message, sizeof(message), 0);

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
#else
int main() { std::cout << "Hello, from Linux!" << std::endl; }
#endif
