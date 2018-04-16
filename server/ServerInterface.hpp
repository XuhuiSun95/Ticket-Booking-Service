#ifndef SERVERINTERFACE_HPP
#define SERVERINTERFACE_HPP

#include <climits>
#include <iomanip>
#include "Server.hpp"

class ServerInterface {

public:

    //  ServerInterface Constructor
    ServerInterface();
    //  ServerInterface Destructor
    ~ServerInterface();

    //  Main loop for ServerInterface
    void Run();

private:

    //  Initialized the interface setting
    void Init();
    //  Display option messages
    void OptionMessage();
    //  Display Server information
    void PrintStatus();
    //  Start the server and handle all requests
    void Host();

    bool mQuit;
    bool mServer;
    std::string mServerName;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
};

#endif
