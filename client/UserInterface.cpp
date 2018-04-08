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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, mServers-1);
    int server = dist(mt);

    client->Init(mServerList[server].first, mServerList[server].second);

    if(client->Valid()) {

        std::string request;
        std::size_t ws;

        std::cout << "Please enter the request in the follow form:" << std::endl;
        std::cout << "<movies, n> or <plays, n>" << std::endl;

        while(true) {

            std::getline(std::cin >> std::ws, request);
            ws = request.find(" ");

            if((request.find("movies")!=std::string::npos
               || request.find("plays")!=std::string::npos)
               && ws!=std::string::npos
               && std::all_of(request.begin()+ws+1, request.end(), ::isdigit)) {
                break;
            } else {
                std::cout << "Invalid input! Please enter the request again." << std::endl;
                request.clear();
            }
        }
        request += "\n";

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
