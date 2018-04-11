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

        mServer->SendMessage(sock, reply);
        std::cout << "Ticket left: " << mTickets << std::endl;
    } else {

        std::cout << "Forward Message!" << std::endl;

        ServerSocket* pair = new ServerSocket();
        pair->Init(mPairInfo.first, mPairInfo.second, false);

        std::string reply = pair->ForwardTicket(msg);
        std::cout << "Receive pair reply: " << reply << std::endl;

        delete pair;

        mServer->SendMessage(sock, reply);
        std::cout << "Forward reply!" << std::endl;
        
    }

    std::cout << std::endl;
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
