#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class ClientSocket {

public:

    ClientSocket();
    ~ClientSocket();

    void Init(const std::string &ipaddress, const int &port);
    bool Valid();
    void RequestTicket(const std::string &message);

private:

    bool mValid;
    int mSockfd, mValread;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
