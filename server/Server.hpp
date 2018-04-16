#ifndef SERVER_HPP
#define SERVER_HPP

#include <mutex>
#include "ServerSocket.hpp"

class Server {

public:

    //  Server Constructor
    //  @param server Server IP address and port number
    //  @param pair Pair IP address and port number
    Server(const std::pair<std::string, int> &server, 
           const std::pair<std::string, int> &pair);
    //  Server Destructor
    ~Server();

    //  Main loop for Server to handle multi thread connection
    //  @param type Server ticket type
    void Run(const std::string &type);

private:

    //  Process the requests from the connection, either handle
    //  on local or forward to pair server
    //  @param sock The socket file descriptor that tring to connect
    //  @param type Server ticket type
    void ProcessTicket(const int &sock, const std::string &type);
    //  Handle purchase request on local server, this function is protected
    //  so there will be not data race during the concurrent events
    //  @param amount The number of tickets client want to buy
    //  @return Either success message or not enough tickets to sale
    std::string HandleRequest(const int &amount);

    int mTickets;
    ServerSocket* mServer;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
    std::mutex mtx;
};

#endif
