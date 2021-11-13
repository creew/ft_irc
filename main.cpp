#include <iostream>
#include "Server.h"


int main() {
    Server server;
    server.start();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
