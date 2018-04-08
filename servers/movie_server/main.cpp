#include <ServerInterface.hpp>

const std::string SERVER_NAME = "Movie";
const std::string SERVER_PORT = "9956";
const std::string SERVER_IP = "localhost";

int main(int argc, char* argv[]) {
    
    ServerInterface* server = new ServerInterface();

    bool quit = false;
    int opt = -1;

    while(!quit) {

        server->GreatingMessage();
        std::cin >> opt;
        switch(opt) {
            case 1:
                server->Init(SERVER_NAME, SERVER_PORT, SERVER_IP);
                break;
            case 2:
                server->ConnPairServer(SERVER_PORT);
                break;
            case 3:
                server->ServerStatus();
                break;
            case 4:
                server->PairStatus();
                break;
            case 5:
                quit = true;
                break;
            default:
                std::cout << "Unknow option! Please enter again." <<std::endl;
        }
    }

    delete server;

    return 0;
}
