#include "UserInterface.hpp"

UserInterface::UserInterface() {

    std::cout << "==================================================" << std::endl;
    std::cout << "||"
              << std::setw(30) << std::right << "User Interface" 
              << std::setw(18) << std::right << "||" << std::endl;
    std::cout << "==================================================" << std::endl;

    mQuit = false;
    mServers = -1;
    mServerList.clear();
}

UserInterface::~UserInterface() {
}

void UserInterface::Run() {

    int opt = -1;

    while(!mQuit) {

        while(mServers<1)
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
                BuyTickets();
                break;
            case 2:
                mQuit = true;
                break;
            default:
                std::cout << "Unknow option! Please enter again." << std::endl;
        }
    }
}

void UserInterface::Init() {

    std::cout << "Initializing Kiosk..." << std::endl;
    std::cout << "Number of server(s) trying to connect: ";
    std::cin >> mServers;
    if(!std::cin.good() || mServers<1) {

        std::cout << "Please enter valid server(s)!" << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        return;
    }

    for(int i=0; i<mServers; i++) {

        std::string address = "";
        int port = -1;

        std::cout << "Enter Server " << i + 1 << " INFO" << std::endl;
        std::cout << std::setw(20) << std::left << "IP address: ";
        std::cin >> address;
        std::cout << std::setw(20) << std::left << "Port: ";
        std::cin >> port;
        if(!std::cin.good() || port<1000) {

            std::cout << "Please enter valid port!" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            mServers = -1;
            return;
        }
        std::cout << std::endl;
        mServerList.push_back(std::make_pair(address, port));
    }
}

void UserInterface::OptionMessage() {

    std::cout << std::endl;
    std::cout << "1. Purchase Tickets" << std::endl;
    std::cout << "2. Quit" << std::endl;
    std::cout << std::endl;
}

void UserInterface::BuyTickets() {

    std::cout << "Processing..." << std::endl;

    Client *client = new Client();
    client->Init(mServerList[0].first, mServerList[0].second);

    if(client->Valid()) {

        std::string request;
        std::cout << "Please enter the request in the follow form:" 
                  << "{buy: <movies, n>} or {buy: <plays, n>}";
        std::getline(std::cin, request);
        client->RequestTicket(request);
    }
    else {

        std::cout << "Socket Init Error! Please check your environment." << std::endl;
        std::cout << std::endl;
        mServers = -1;
        mServerList.clear();
    }

    delete client;
}
