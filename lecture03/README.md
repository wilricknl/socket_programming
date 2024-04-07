# Lecture 3

### Socket

A socket is a combination of an IP address and a port.

* IP address: identifies a device
* Port: identifies some process or application on a device. In fact a program creates a socket, which exposes communication with the world.

### Internet address representation in C

```cpp
struct sockaddr_in
{
    sa_family_t     sin_family;
    uint16_t        sin_port;
    struct in_addr  sin_addr;
    char            sin_zero[8];
}

struct in_addr
{
    in_addr_t       s_addr;
}
```

### Endian-ness

When communicating over a network, it's essential to ensure that data is transmitted and received in a consistent byte order to avoid confusion and errors. Therefore, before sending data over a network, you typically convert values from the host byte order to the network byte order using `htons()`. Conversely, when receiving data from the network, you would convert values from network byte order to host byte order using the `ntohs()` (network to host short) function.

```cpp
// Host to Network short
unsigned short htons(unsigned short);

// Network to Host short
unsigned short ntohs(unsigned short);

// Host to Network long
unsigned long htonl(unsigned long);

// Network to Host long
unsigned long ntohl(unsigned long);
```

### Allowing any client to connect

For this you can use `INADDR_ANY` which represents `0.0.0.0`. Furthermore, there also exists `INADDR_LOOPBACK` which represents the local host `127.0.0.1`. Finally, `INADDR_NONE` with value `255.255.255.255` blocks all connections.

```cpp
struct sockaddr_in address;
address.sin_addr.s_addr = htonl(INADDR_ANY);
```

### IP address conversions

There are two functions `inet_aton()` (address to network) and `inet_ntoa()` (network to address) that can convert between a 32-bit network integer representation and a dotted-decimal (e.g. `"127.0.0.1"`) representation. More info [here](https://www.gta.ufrj.br/ensino/eel878/sockets/inet_ntoaman.html).

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct in_addr addr;
    addr.s_addr = inet_addr("192.168.1.1");

    // points to static buffer managed by inet_ntoa, no need to free,
    // but it gets overwritten each invocation
    char *ip_address = inet_ntoa(addr);
    if(ip_address == NULL) {
        perror("inet_ntoa");
        exit(EXIT_FAILURE);
    }

    printf("IP Address: %s\n", ip_address);

    return 0;
}
```
