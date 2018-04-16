#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class ServerSocket {

public:

    //  ServerSocket Constructor
    ServerSocket();
    //  ServerSocket Destructor
    ~ServerSocket();

    //  Function used to initialize socket
    //  @param ipaddress The socket IP address
    //  @param port The socket port number
    //  @param host True if create a host socket, otherwise create a forward socket
    void Init(const std::string &ipaddress, const int &port, bool host=true);
    //  Check if ServerSocket initialize correctly
    bool Valid();
    //  Accept the connecting clients
    //  @return The accepted socket file descriptor
    int Accept();
    //  Read message sent from accepted client
    //  @param sock The socket file descriptor that trying to read
    //  @return The message received in string
    std::string GetMessage(const int &sock);
    //  Send back message to pervious client
    //  @param sock The socket file descriptor that trying to send
    //  @param message The reply message
    void SendMessage(const int &sock, const std::string &message);
    //  Forward message to the pair server if the requested type 
    //  ticket is not sold on this server
    //  @param message Message needs to forward
    //  @return Message replied from the pair server
    std::string ForwardTicket(const std::string &message);

private:

    bool mValid;
    int mSockfd, mValread;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
