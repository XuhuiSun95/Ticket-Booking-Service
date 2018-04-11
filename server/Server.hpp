#ifndef SERVER_HPP
#define SERVER_HPP

#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include "ServerSocket.hpp"

class Server {

public:

    Server(const std::pair<std::string, int> &server, 
           const std::pair<std::string, int> &pair);
    ~Server();

    bool Valid();
    void Run(const std::string &type);

private:

    void ProcessTicket(const int &sock, const std::string &type);
    std::string HandleRequest(const int &amount);

    bool mValid;
    int mTickets;
    ServerSocket* mServer;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
    std::mutex mtx;
};

#endif
