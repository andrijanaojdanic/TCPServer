#include "TCPServer.hpp"

TCPServer::TCPServer(int _port): port(_port){
    serverSocketFd = 0;
}

void TCPServer::initServer(){
    // Create socket
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);    
    if (serverSocketFd < 0)
    { 
        throw ServerException("Error creating socket.");
    }
    else
    {
        throw ServerException("All good!");
    }
}
