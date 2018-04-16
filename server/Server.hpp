#ifndef SERVER_HPP
#define SERVER_HPP

#include <mutex>
#include "ServerSocket.hpp"

class Server {

public:

    Server(const std::pair<std::string, int> &server, 
           const std::pair<std::string, int> &pair);
    ~Server();

    void Run(const std::string &type);

private:

    void ProcessTicket(const int &sock, const std::string &type);
    std::string HandleRequest(const int &amount);

    int mTickets;
    ServerSocket* mServer;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
    std::mutex mtx;
};

#endif
