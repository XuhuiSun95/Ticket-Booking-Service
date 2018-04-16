#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class ClientSocket {

public:

    //  ClientSocket Constructor
    ClientSocket();
    //  ClientSocket Destructor
    ~ClientSocket();

    //  Initialize the ClientSocket(socket and connect)
    //  @param ipaddress The IP address going to connect
    //  @param port The port number going to connect
    void Init(const std::string &ipaddress, const int &port);
    //  Check if the initialization is valid
    //  @return True if successful connected, otherwise return False
    bool Valid();
    //  Send request message to the connected server
    //  @param message The request message
    void RequestTicket(const std::string &message);

private:

    bool mValid;
    int mSockfd, mValread;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
