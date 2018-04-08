#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>
#include "Client.hpp"

class UserInterface {

public:

    UserInterface();
    ~UserInterface();

    void Run();

private:

    void Init();
    void OptionMessage();
    void BuyTickets();

    bool mQuit;
    int mServers;
    std::vector<std::pair<std::string, int>> mServerList;
};

#endif
