#ifndef SERVERINTERFACE_HPP
#define SERVERINTERFACE_HPP

#include <iostream>
#include <iomanip>
#include <string>

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
    int mTickets;
    std::string mServerName;
    std::pair<std::string, int> mServerInfo;
    std::pair<std::string, int> mPairInfo;
};

#endif
