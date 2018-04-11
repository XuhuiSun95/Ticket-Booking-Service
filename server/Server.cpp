#include "Server.hpp"

Server::Server(const std::pair<std::string, int> &server,
               const std::pair<std::string, int> &pair) {

    mValid = false;
    mTickets = 50;
    mServer = new ServerSocket();
    mServerInfo = server;
    mPairInfo = pair;
}

Server::~Server() {

    delete mServer;
}

bool Server::Valid() {

    return mValid;
}

void Server::Run(const std::string &type) {

    mServer->Init(mServerInfo.first, mServerInfo.second, true);
    mValid = mServer->Valid();

    while(true) {

        int sockfd = mServer->Accept();
        std::thread (&Server::ProcessTicket, sockfd, type).detach();
    }
}

void Server::ProcessTicket(const int &sock, const std::string &type) {

    std::string msg = mServer->GetMessage(sock);

    if(msg.find(type)!=std::string::npos) {

        std::size_t ws = msg.find(" ");
        int ticket = std::stoi(msg.substr(ws+1));
        
        mtx.lock();
        std::string reply = HandleRequest(ticket);
        mtx.unlock();

        mServer->SendMessage(sock, reply);

    } else {

        
    }
}

std::string Server::HandleRequest(const int &amount) {

    int left = mTickets - amount;

    if(left < 0) {
        return "Not enought ticket to sale!";
    }
    else {

        mTickets = mTickets - amount;
        return "Success!";
    }
}
