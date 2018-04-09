#include "ServerInterface.hpp"

int main(int argc, char* argv[]) {

    ServerInterface* server = new ServerInterface();

    server->Run();

    delete server;

    return 0;
}
