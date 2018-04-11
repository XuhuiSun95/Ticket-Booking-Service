#ifndef SERVERINTERFACE_HPP
#define SERVERINTERFACE_HPP

#include <iomanip>
#include "Server.hpp"

class ServerInterface {

public:

    ServerInterface();
    ~ServerInterface();

    void Run();

private:

    void Init();
    void OptionMessage();
    void PrintStatus();
    void Host();

    bool mQuit;
    bool mServer;
    std::string mServerName;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
};

#endif
