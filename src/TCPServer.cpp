#include "TCPServer.hpp"

TCPServer::TCPServer(uint16_t _port, uint32_t _address, uint16_t _maxNumOfClients): 
    port(_port), 
    address(_address),
    maxNumOfClients(_maxNumOfClients)
{
    serverSocketFd = 0;

    serverInterface.sin_family = AF_INET;
    serverInterface.sin_port   = htons(port), // htons = Host To Network Short, makes sure that bytes are stored in network data order
    serverInterface.sin_addr.s_addr = htonl(address); // htonl = Host To Network Long, works with 32b integers

    clientAddressLen = sizeof(struct sockaddr);

}

void TCPServer::initServer() 
{
    // Create socket
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);    
    if (serverSocketFd < 0)
    { 
        throw ServerException("Error creating socket");  
    }

    // Bind socket to internet addr
    if (bind(serverSocketFd, (struct sockaddr *)&serverInterface, sizeof(serverInterface)) != 0)
    {
        throw ServerException("Error binding socket");   
    }

    // Put socket in server mode - listen to connections
    if (listen(serverSocketFd, maxNumOfClients) != 0)
    {
        throw ServerException("Error putting socket in server mode");   
    }
    
}

void TCPServer::acceptConnection()
{
    std::cout << "Waiting for connection..." << std::endl; // TODO postace Terminal.writeln("Waiting for connection...");

    // Accept connection
    clientSocketFd = accept(serverSocketFd, &clientAddress, &clientAddressLen);
    if (clientSocketFd < 0)
    {
        throw ServerException("Error accepting connection");
    }
}

void TCPServer::receiveMessage()
{
    while(true){
        // Receive Message
        int msgSize = recv(clientSocketFd, recv_buffer, 1024, 0);
        if (msgSize == -1)
        {
            throw ServerException("Error receiving from client");    
        }
        else if (msgSize == 0)
        {
            close(clientSocketFd);
            std::cout << "Connection with client " << clientSocketFd << " ended." << std::endl;
            break;
        }
        else
        {
            std::cout << "Received message: " << recv_buffer << std::endl;
            // Echo Message
            if (!send(clientSocketFd, recv_buffer, msgSize, 0))
            {
                throw ServerException("Error sending echo message back");                    
            }
        }
    }
}

