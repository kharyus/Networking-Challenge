#include "Client.h"

#include <iostream>

namespace cl
{
    Client::Client()
    {
        // Sets socket as non-blocking.
        socket.setBlocking(false);
    }

    Client::~Client()
    {
        // Join all threads
        receiveThread.join();

        socket.disconnect();
    }

    void Client::connect(const std::string& ip, unsigned short port)
    {
        // Wait for the connection to be established
        while (socket.connect(ip, port) != sf::Socket::Done);
        std::cout << "Connection successful to " << ip <<"!" << "\n";

        // Create temporary thread and swap it with this instance's thread.
        std::thread tempThread(receiveThreadFunc, this);
        std::swap(tempThread, receiveThread);

        // Send Loop runs on Main thread
        sendLoop();
    }

    void Client::sendLoop()
    {
        std::string s;
        sf::Packet packet;
        while (running)
        {
            std::cin >> s;
            packet << s;
            socket.send(packet);
            if (s == "QUIT")
            {
                running = false;
            }
            packet.clear();
        }
    }

    void Client::receiveThreadFunc()
    {
        std::string s;
        sf::Packet packet;
        while (running)
        {
            sf::Socket::Status status = socket.receive(packet);
            if (status == sf::Socket::Done)
            {
                packet >> s;
                std::cout << s << '\n';
                packet.clear();
            }
            else if (status == sf::Socket::Disconnected)
            {
                running = false;
                socket.disconnect();
            }
        }
    }
}
