#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <list>

namespace sv
{
    class Server
    {
        public:
            Server();
            virtual ~Server();

        protected:
        private:
            // Client Struct
            struct Client{
                sf::TcpSocket socket;
                std::thread thread;
                unsigned long id;
                unsigned short cardsSum;
                bool askedStart = false;
            };

            // Data
            sf::TcpListener listener;
            std::thread listenerThread;
            std::list<Client> clients; // Had to use List because Sockets are non-copyable and non-movable.
            std::vector<std::thread> clientThreads;
            bool running = true;
            bool listening = true;

            // Functions
            void startListening();
            void listenerThreadFunc();
            void clientThreadFunc(Client* client);
            const std::string drawCard();
            void sendToEveryOtherClient(const std::string& message, const unsigned long id);
    };
}

#endif // SERVER_H
