#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class ServerSocket {

public:

    ServerSocket();
    ~ServerSocket();

    void Init(const std::string &ipaddress, const int &port, bool host=true);
    bool Valid();
    int Accept();
    std::string GetMessage(const int &sock);
    void SendMessage(const int &sock, const std::string &message);
    std::string ForwardTicket(const std::string &message);

private:

    bool mValid;
    int mSockfd, mValread;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
