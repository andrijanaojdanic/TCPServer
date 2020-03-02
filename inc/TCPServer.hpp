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

private:

    int serverSocketFd; // initialized
    uint16_t port;
    uint32_t address;
    uint16_t maxNumOfClients;    
    uint16_t receiveBufferSize;
    uint16_t sendBufferSize;
    struct sockaddr_in serverInterface;    

    typedef struct{
        int socketFd;
        int vectorPosition;
        struct sockaddr address;
        char * receiveBuffer;
        char * sendBuffer;
        socklen_t addressLen;
    } Client;

    std::vector<Client*> clients;

    int clientSocketFd;
    struct sockaddr clientAddress;
    char * receiveBuffer;
    char * sendBuffer;
    socklen_t clientAddressLen; // initialized

    void createSocket();    // TODO implementirati ovo zarad lepote koda
    void bindSocket();      // TODO implementirati ovo zarad lepote koda
    void startListening();  // TODO implementirati ovo zarad lepote koda

public:

    TCPServer(uint16_t _port=5000, 
              uint32_t _address=INADDR_ANY, 
              uint16_t _maxNumOfClients=10,
              uint16_t _rcvBufSize=1024,
              uint16_t _sndBufSize=1024);
    ~TCPServer();

    void initServer();  // throws ServerException
    void runServer(); // TODO potentially put functionality here
    void acceptConnection(); // throws ServerException
    void receiveMessage(); // throws ServerException
    void sendMessage(); // throws ServerException
    void closeConnection();

    // Getters TODO
    uint16_t getPort();
    uint32_t getAddress();
    uint16_t getMaxNumOfClients();
    uint16_t getReceiveBufferSize();
    uint16_t getSendBufferSize();
};

#endif
