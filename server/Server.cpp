#include "Server.hpp"

Server::Server(const std::pair<std::string, int> &server,
               const std::pair<std::string, int> &pair) {

    mTickets = 50;
    mServer = new ServerSocket();
    mServerInfo = server;
    mPairInfo = pair;
}

Server::~Server() {

    delete mServer;
}

void Server::Run(const std::string &type) {

    mServer->Init(mServerInfo.first, mServerInfo.second, true);

    while(true) {

        int sockfd = mServer->Accept();
        std::thread t(&Server::ProcessTicket, this, sockfd, type);
        t.detach();
    }
}

void Server::ProcessTicket(const int &sock, const std::string &type) {

    std::string msg = mServer->GetMessage(sock);
    std::cout << "Message Received: " << msg << std::endl;

    if(msg.find(type)!=std::string::npos) {

        std::size_t ws = msg.find(" ");
        int ticket = std::stoi(msg.substr(ws+1));
        
        mtx.lock();
        std::string reply = HandleRequest(ticket);
        mtx.unlock();
        std::cout << "Ticket left: " << mTickets << std::endl;

        mServer->SendMessage(sock, reply);
    } else {

        ServerSocket* pair = new ServerSocket();
        pair->Init(mPairInfo.first, mPairInfo.second, false);

        std::cout << "Forward Message!" << std::endl;
        std::string reply = pair->ForwardTicket(msg);
        std::cout << "Receive pair reply: " << reply << std::endl;

        delete pair;

        std::cout << "Forward reply!" << std::endl;
        mServer->SendMessage(sock, reply);
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
