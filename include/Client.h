#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <thread>

namespace cl
{
    class Client
    {
        public:
            Client();
            virtual ~Client();

            void connect(const std::string& ip, unsigned short port);

        protected:
        private:
            sf::TcpSocket socket;
            std::thread receiveThread;
            bool running = true;

            // Functions
            void sendLoop();
            void receiveThreadFunc();
    };
}

#endif // CLIENT_H
