# Lecture 1: introduction

### Hello, client & server

#### Operating system

Linux/Apple (not tested)

#### Terminal 1

Start the server listening on port `1234`.

```shell
./01_hello_server 1234
```

#### Terminal 2

Connect a client to the local server, hence IP `127.0.0.1`, running on port `1234`.

```shell
./01_hello_client 127.0.0.1 1234
```
