#include "ServerInterface.hpp"

ServerInterface::ServerInterface() {

    std::cout << "==================================================" << std::endl;
    std::cout << "||"
              << std::setw(31) << std::right << "Server Interface" 
              << std::setw(17) << std::right << "||" << std::endl;
    std::cout << "==================================================" << std::endl;

    mQuit = false;
    mServer = false;
}

ServerInterface::~ServerInterface() {
}

void ServerInterface::Run() {

    int opt = -1;

    while(!mQuit) {

        while(mServerName.empty())
            Init();

        OptionMessage();
        std::cin >> opt;
        if(!std::cin.good()) {

            std::cout << "Unknow option! Please enter again." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        switch(opt) {
            case 1:
                PrintStatus();
                break;
            case 2:
                Host();
                break;
            case 3:
                mQuit = true;
                break;
            default:
                std::cout << "Unknow option! Please enter again." << std::endl;
        }
    }
}

void ServerInterface::Init() {

    std::cout << "Initializing Server..." << std::endl;
    std::cout << "Vending ticket type (movies or plays): ";
    std::cin >> mServerName;
    if(mServerName.compare("movies")!=0 && mServerName.compare("plays")!=0) {

        std::cout << "Please enter valid type!" << std::endl;
        mServerName = "";
        return;
    }

    std::string address = "";
    int port = -1;

    std::cout << "Enter Server INFO" << std::endl;
    std::cout << std::setw(20) << std::left << "IP address: ";
    std::cin >> address;
    std::cout << std::setw(20) << std::left << "Port: ";
    std::cin >> port;
    if(!std::cin.good() || port<1000) {

        std::cout << "Please enter valid port!" << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        mServerName = "";
        return;
    }
    std::cout << std::endl;
    mServerInfo = std::make_pair(address, port);

    std::cout << "Enter Pair Server INFO" << std::endl;
    std::cout << std::setw(20) << std::left << "IP address: ";
    std::cin >> address;
    std::cout << std::setw(20) << std::left << "Port: ";
    std::cin >> port;
    if(!std::cin.good() || port<1000) {

        std::cout << "Please enter valid port!" << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        mServerName = "";
        return;
    }
    std::cout << std::endl;
    mPairInfo = std::make_pair(address, port);
}

void ServerInterface::OptionMessage() {

    std::cout << std::endl;
    std::cout << "1. Server Status" << std::endl;
    std::cout << "2. Host Server" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << std::endl;
}

void ServerInterface::PrintStatus() {

    if(mServer)
        std::cout << "Server [" << mServerName << "] is current running..." << std::endl;
    else
        std::cout << "Server [" << mServerName << "] is waiting for host..." << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "|" 
              << std::setw(30) << std::right << "Server INFO"
              << std::setw(19) << std::right << "|" << std::endl;
    std::cout << std::setw(48 - mServerInfo.first.length()) 
              << std::left << "| ip address: " << mServerInfo.first
              << " |" << std::endl;
    std::cout << std::setw(48 - std::to_string(mServerInfo.second).length()) 
              << std::left << "| port #: " << mServerInfo.second
              << " |" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "|" 
              << std::setw(32) << std::right << "Pair Server INFO"
              << std::setw(17) << std::right << "|" << std::endl;
    std::cout << std::setw(48 - mPairInfo.first.length()) 
              << std::left << "| ip address: " << mPairInfo.first
              << " |" << std::endl;
    std::cout << std::setw(48 - std::to_string(mPairInfo.second).length()) 
              << std::left << "| port #: " << mPairInfo.second
              << " |" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
}

void ServerInterface::Host() {

    std::cout << "Hosting..." << std::endl;
    mServer = true;

    Server *server = new Server(mServerInfo, mPairInfo);

    if(server->Valid()) {

        server->Run(mServerName);
    }
    else {

        std::cout << "Server Init Error! Please check your environment." << std::endl;
        std::cout << std::endl;

        mServerName = "";
    }

    delete server;
    mServer = false;
}
