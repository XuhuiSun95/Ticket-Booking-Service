#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Client {

public:

    Client();
    ~Client();

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
