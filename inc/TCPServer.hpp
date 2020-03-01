#ifndef __TCP_SERVER_HPP_
#define __TCP_SERVER_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include "ServerException.hpp"

class TCPServer {
    
    int port;
    int serverSocketFd; // initialized
    struct sockaddr_in serverAddress;    
    std::vector<struct sockaddr> clients;
    static constexpr int clientAddressLen = sizeof(struct sockaddr);

    void createSocket();
    void bindSocket();
    void startListening();

public:

    TCPServer(int _port=5000); // TODO add address at some point
    void initServer();
    void runServer(); // TODO potentially put functionality here
    void acceptConnection();
    void receiveMessage();
    void sendMessage();
    void closeConnection();
};

#endif
