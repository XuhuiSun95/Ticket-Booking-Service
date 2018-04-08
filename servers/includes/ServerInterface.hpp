#ifndef SERVERINTERFACE_HPP
#define SERVERINTERFACE_HPP

#include <iostream>
#include <iomanip>
#include <string>

class ServerInterface {

public:

    ServerInterface();
    ~ServerInterface();

    void Init(std::string name, std::string port, std::string ipaddress = "localhost");

    void ConnPairServer(std::string port, std::string ipaddress = "localhost");

    void GreatingMessage();

    void ServerStatus();

    void PairStatus();

private:

    std::string mServerName;
    std::string mServerPort;
    std::string mServerIpaddress;
    std::string mPairPort;
    std::string mPairIpaddress;
    int mTickets;
    bool mStatus;
    bool mPairConn;
};

#endif
