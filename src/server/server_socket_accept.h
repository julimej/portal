#ifndef SOCKET_ACCEPT
#define SOCKET_ACCEPT

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "../common/common_socket_connect.h"

class SocketAccept {
    private:
        int s;
        int skt;
        int opt;
        struct addrinfo hints;
        struct addrinfo *ptr;
        void setHints(); 

    public:
        SocketAccept();
        ~SocketAccept();
        void closeSocket();
        SocketConnect acceptSocket();
        bool listenSocketAccept();
        bool bindSocketAccept();
        bool sktOpciones();
        bool addrinfo(char *srvn);
        bool sktSocketAccept();
        bool socketIsValid();
        void setSocketToInvalid();
        SocketAccept& operator=(const SocketAccept&) = delete;
        SocketAccept(SocketAccept&& other);
        SocketAccept& operator=(SocketAccept&& other);
};

#endif
