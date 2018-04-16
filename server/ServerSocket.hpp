#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <chrono>
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
    //  Check if Socket Init() correctly
    bool Valid();
    //  Function used to accept clients
    //  return the socket file descriptor
    int Accept();
    //  Function used to read message sent from client
    std::string GetMessage(const int &sock);
    //  Function used to send back message to client
    void SendMessage(const int &sock, const std::string &message);
    //  Function used to forward message to other server
    //  if the requested type ticket is sold on other server
    //  return message get back from other server
    std::string ForwardTicket(const std::string &message);

private:

    bool mValid;
    int mSockfd, mValread;
    struct sockaddr_in mAddress;
    char buffer[1024];
};

#endif
