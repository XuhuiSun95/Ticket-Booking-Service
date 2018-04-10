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
    int AcceptLoop();
    std::string HandleRequest();
    void ForwardTicket();

private:

    bool mValid;
    int mSockfd, mValread;
    std::vector<int> mClientList;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
