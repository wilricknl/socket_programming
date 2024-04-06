# Lecture 2

### Sockets

#### Function

```cpp
int socket(int domain, int type, int protocol)
```

#### Domain

| Domain   | Description |
| -------- | ----------- |
| AF_INET  | IPv4        |
| AF_INET6 | IPv6        |

#### Type

| Type        | Description |
| ----------- | ----------- |
| SOCK_STREAM | TCP         |
| SOCK_DGRAM  | UDP         |

#### Protocol

| Number | Protocol |
| ------ | -------- |
| 0      | IP       |
| 6      | TCP      |
| 17     | UDP      |

Find other available protocols using `cat /etc/protocols`.
