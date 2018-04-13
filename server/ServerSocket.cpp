#include "ServerSocket.hpp"

ServerSocket::ServerSocket() {

    memset(buffer, 0, sizeof(buffer));
    mValid = false;
}

ServerSocket::~ServerSocket() {

    close(mSockfd);
}

//function used to initialize socket
void ServerSocket::Init(const std::string &ipaddress, const int &port, bool host) {

    if((mSockfd = socket(AF_INET, SOCK_STREAM, 0))==0) {
        std::cout << "Socket creation error" << std::endl;
        return;
    }
    
    //setup socket address structure
    memset(&mAddress, '0', sizeof(mAddress));
    mAddress.sin_family = AF_INET;
    mAddress.sin_port = htons(port);

    if(host) {

        mAddress.sin_addr.s_addr = INADDR_ANY;
        // call bind to associate the socket with our local address and
        // port
        if(bind(mSockfd, (struct sockaddr *)&mAddress, sizeof(mAddress))<0) {
            std::cout << "Bind Failed" << std::endl;
            return;
        }
        // convert the socket to listen for incoming connections
        if(listen(mSockfd, 10)<0) {
            std::cout << "Listen Failed" << std::endl;
            return;
        }
    }
    else {
        
        if(inet_pton(AF_INET, ipaddress.c_str(), &mAddress.sin_addr)<=0) {
            std::cout << "Invalid pair server address/ Address not supported" << std::endl;
            return;
        }

        if(connect(mSockfd, (struct sockaddr *)&mAddress, sizeof(mAddress))<0) {
            std::cout << "Connection Failed" << std::endl;
            return;
        }
    }

    mValid = true;
}

bool ServerSocket::Valid() {

    return mValid;
}

//function used to accept clients, return number greater than 0 if success
int ServerSocket::Accept() {

    int addrlen = sizeof(mAddress);
    int new_socket;
    
    if((new_socket = accept(mSockfd, (struct sockaddr *)&mAddress, (socklen_t*)&addrlen))<0) {
        std::cout << "Accept Failed" << std::endl;
        return -1;
    }

    return new_socket;
}

//function used to read message sent from client.
std::string ServerSocket::GetMessage(const int &sock) {

    mValread = read(sock, buffer, 1024);
    std::string message = buffer;
    memset(buffer, 0, sizeof(buffer));
    
    return message;
}

//function used to send back message to client
void ServerSocket::SendMessage(const int &sock, const std::string &message) {

    send(sock, message.c_str(), message.length(), 0);

    close(sock);
}

//function used to forward message to other server
//if the requested type ticket is sold on other server
//return message get back from other server
std::string ServerSocket::ForwardTicket(const std::string &message) {

    send(mSockfd, message.c_str(), message.length(), 0);

    mValread = read(mSockfd, buffer, 1024);

    std::string reply = buffer;

    return reply;
}
