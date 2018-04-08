#include "UserInterface.hpp"

int main(int argc, char* argv[]) {

    UserInterface* user = new UserInterface();

    user->Run();

    delete user;

    return 0;
}
