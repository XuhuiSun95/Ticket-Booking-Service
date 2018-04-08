#include "ServerInterface.hpp"

ServerInterface::ServerInterface() {

    std::cout << "==================================================" << std::endl;
    std::cout << "||"
              << std::setw(31) << std::right << "Server Interface" 
              << std::setw(17) << std::right << "||" << std::endl;
    std::cout << "==================================================" << std::endl;

    mServerName = "";
    mServerPort = "";
    mServerIpaddress = "";
    mPairPort = "";
    mPairIpaddress = "";
    mTickets = 50;
    mStatus = false;
    mPairConn = false;
}

ServerInterface::~ServerInterface() {
}

void ServerInterface::Init(std::string name, std::string port, std::string ipaddress) {

    if(mStatus) {
        std::cout << "Server already established!" << std::endl;
        return;
    }

    mServerName = name;
    mServerPort = port;
    mServerIpaddress = ipaddress;

    // Inital server 

    std::cout << "Server [" << mServerName << "] established!" << std::endl;

    mStatus = true;
}

void ServerInterface::ConnPairServer(std::string port, std::string ipaddress) {

    if(mPairConn) {
        std::cout << "Pair Server already connected!" << std::endl;
        return;
    }

    mPairPort = port;
    mPairIpaddress = ipaddress;

    // Connect pair server

    std::cout << "Pair Server Connection Established!" << std::endl;

    mPairConn = true;
}

void ServerInterface::GreatingMessage() {

    std::cout << std::endl;
    std::cout << "1. Create Server" << std::endl;
    std::cout << "2. Connect Pair Server" << std::endl;
    std::cout << "3. Server Status" << std::endl;
    std::cout << "4. Pair Server Status" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << std::endl;
}

void ServerInterface::ServerStatus() {

    if(mStatus) {

        std::cout << "Server [" << mServerName << "] is current running..." << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "|" 
                  << std::setw(30) << std::right << "Server INFO"
                  << std::setw(19) << std::right << "|" << std::endl;
        std::cout << std::setw(48 - mServerIpaddress.length()) 
                  << std::left << "| ip address: " << mServerIpaddress 
                  << " |" << std::endl;
        std::cout << std::setw(48 - mServerPort.length()) 
                  << std::left << "| port #: " << mServerPort
                  << " |" << std::endl;
        std::cout << std::setw(48 - std::to_string(mTickets).length())
                  << std::left << "| Tickets left: " << mTickets 
                  << " |" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }
    else
        std::cout << "Server is not established! Please check back later." << std::endl;
}

void ServerInterface::PairStatus() {

    if(mPairConn)
        std::cout << "Pair Server connected." << std::endl;
    else
        std::cout << "Connection is not established!" << std::endl;
}
