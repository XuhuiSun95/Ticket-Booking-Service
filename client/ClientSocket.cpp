#include "ClientSocket.hpp"

ClientSocket::ClientSocket() {

    memset(buffer, 0, sizeof(buffer));
    mValid = false;
}

ClientSocket::~ClientSocket() {

    close(mSockfd);
}

void ClientSocket::Init(const std::string &ipaddress, const int &port) {

    if((mSockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        std::cout << "Socket creation error" << std::endl;
        return;
    }
    memset(&mAddress, '0', sizeof(mAddress));

    mAddress.sin_family = AF_INET;
    mAddress.sin_port = htons(port);

    if(inet_pton(AF_INET, ipaddress.c_str(), &mAddress.sin_addr)<=0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    if(connect(mSockfd, (struct sockaddr *)&mAddress, sizeof(mAddress))<0) {
        std::cout << "Connection Failed" << std::endl;
        return;
    }

    mValid = true;
}

bool ClientSocket::Valid() {
    
    return mValid;
}

void ClientSocket::RequestTicket(const std::string &message) {

    std::cout << "Request send" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    send(mSockfd, message.c_str(), message.length(), 0);

    mValread = read(mSockfd, buffer, 1024);
    std::cout << buffer << std::endl;
}
