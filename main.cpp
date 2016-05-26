#include <Client.h>
#include <Server.h>
#include <iostream>

int main()
{
    // Declare variables
    char clientOrServer;
    std::string ip;

    // Select client or server
    std::cout << "Are you a (c)lient or (s)erver? ";
    std::cin >> clientOrServer;

    if (clientOrServer == 'c')
    {
        // Select ip
        std::cout << "What is the ip? ";
        std::cin >> ip;

        cl::Client client;
        client.connect(ip, 53000);
    }
    else if (clientOrServer == 's')
    {
        sv::Server server;
    }

    return 0;
}
