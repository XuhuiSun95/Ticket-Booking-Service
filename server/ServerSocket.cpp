#include "ServerSocket.hpp"

ServerSocket::ServerSocket() {

    memset(buffer, 0, sizeof(buffer));
    mValid = false;
}

ServerSocket::~ServerSocket() {

    close(mSockfd);
}

void ServerSocket::Init(const std::string &ipaddress, const int &port, bool host) {

    if((mSockfd = socket(AF_INET, SOCK_STREAM, 0))==0) {
        std::cout << "Socket creation error" << std::endl;
        return;
    }
    memset(&mAddress, '0', sizeof(mAddress));

    mAddress.sin_family = AF_INET;
    mAddress.sin_port = htons(port);

    if(host) {

        mAddress.sin_addr.s_addr = INADDR_ANY;

        if(bind(mSockfd, (struct sockaddr *)&mAddress, sizeof(mAddress))<0) {
            std::cout << "Bind Failed" << std::endl;
            return;
        }

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

int ServerSocket::Accept() {

    int addrlen = sizeof(mAddress);
    int new_socket;

    if((new_socket = accept(mSockfd, (struct sockaddr *)&mAddress, (socklen_t*)&addrlen))<0) {
        std::cout << "Accept Failed" << std::endl;
        return -1;
    }

    return new_socket;
}

std::string GetMessage(const int &sock) {

    char* buf = new char[1024];
    //mValread = read(sock, buf, 1024);
    read(sock, buf, 1024);
    std::string message = buf;
    delete[] buf;
    
    return message;
}

void ServerSocket::SendMessage(const int &sock, const std::string &message) {

    send(sock, message.c_str(), message.length(), 0);

    close(sock);
}

void ServerSocket::ForwardTicket() {


}
