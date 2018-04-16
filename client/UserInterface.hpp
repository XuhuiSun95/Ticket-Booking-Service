#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>
#include "ClientSocket.hpp"

class UserInterface {

public:

    //  UserInterface Constructor
    UserInterface();
    //  UserInterface Destructor
    ~UserInterface();

    //  Main loop for UserInterface
    void Run();

private:

    //  Save the server(s) Infomation and perform input check
    void Init();
    //  Display the option messages
    void OptionMessage();
    //  Randomly choose from the serves list and perform ticket purchase operation
    void BuyTickets();

    bool mQuit;
    int mServers;
    std::vector<std::pair<std::string, int>> mServerList;
};

#endif
