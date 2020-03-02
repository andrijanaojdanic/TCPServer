#ifndef __TCP_SERVER_HPP_
#define __TCP_SERVER_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <cstdint>
#include "ServerException.hpp"
#include <unistd.h>

class TCPServer {
    
    int serverSocketFd; // initialized
    uint16_t port;
    uint32_t address;
    uint16_t maxNumOfClients;    
    struct sockaddr_in serverInterface;    

    int clientSocketFd;
    struct sockaddr clientAddress;
    char recv_buffer[1024];
    socklen_t clientAddressLen; // initialized

    void createSocket();
    void bindSocket();
    void startListening();

public:

    TCPServer(uint16_t _port=5000, uint32_t _address=INADDR_ANY, uint16_t _maxNumOfClients=10);

    void initServer();  // throws ServerException
    void runServer(); // TODO potentially put functionality here
    void acceptConnection(); // throws ServerException
    void receiveMessage(); // throws ServerException
    void sendMessage(); // throws ServerException
    void closeConnection();
};

#endif
