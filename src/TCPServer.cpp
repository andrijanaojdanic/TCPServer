#include "TCPServer.hpp"

TCPServer::TCPServer(uint16_t _port, uint32_t _address, uint16_t _maxNumOfClients, uint16_t _rcvBufSize, uint16_t _sndBufSize): 
    port(_port), 
    address(_address),
    maxNumOfClients(_maxNumOfClients),
    receiveBufferSize(_rcvBufSize),
    sendBufferSize(_sndBufSize)
{
    serverSocketFd = 0;
    
    serverInterface.sin_family = AF_INET;
    serverInterface.sin_port   = htons(port), // htons = Host To Network Short, makes sure that bytes are stored in network data order
    serverInterface.sin_addr.s_addr = htonl(address); // htonl = Host To Network Long, works with 32b integers

    clientAddressLen = sizeof(struct sockaddr);
    receiveBuffer = new char[receiveBufferSize];
}

TCPServer::~TCPServer()
{
    delete [] receiveBuffer;
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

    Client* client = new(std::nothrow) Client;
    client->addressLen = sizeof(client->address);

    // Accept connection
    client->socketFd = accept(serverSocketFd, (struct sockaddr *)(&(client->address)), &(client->addressLen));
    if (client == nullptr)
    {
        throw ServerException("Memory allocation failed");
    }
    else if (client->socketFd < 0)
    {
        delete client;
        throw ServerException("Error accepting connection");
    }
    client->vectorPosition = clients.size();
    client->address.sin_family = AF_INET;
    client->receiveBuffer = new char[receiveBufferSize];
    client->sendBuffer = new char[sendBufferSize];
    clients.push_back(client);

    std::cout << "Client: " << std::endl 
              << "socketFd" << client->socketFd << std::endl   
              << "vectorPosition" << client->vectorPosition << std::endl      
              << "address" << inet_ntoa(client->address.sin_addr) << std::endl  
              << "port" << ntohs(client->address.sin_port) << std::endl 
              << "addressLen" << client->socketFd << std::endl;
}

void TCPServer::receiveMessage()
{
    const Client* client = clients.at(0);

    while(true){
        // Receive Message
        int msgSize = recv(client->socketFd, client->receiveBuffer, receiveBufferSize, 0);
        if (msgSize == -1)
        {
            throw ServerException("Error receiving from client");    
        }
        else if (msgSize == 0)
        {
            close(client->socketFd);
            clients.erase(clients.begin()+client->vectorPosition);
            delete[] client->receiveBuffer;
            delete[] client->sendBuffer;
            delete client;
            std::cout << "Connection with client " << client->socketFd << " ended." << std::endl;
            break;
        }
        else
        {
            client->receiveBuffer[msgSize] = '\0';
            std::cout << "Received message: " << client->receiveBuffer << std::endl;
            // Echo Message
            if (!send(client->socketFd, client->receiveBuffer, msgSize, 0))
            {
                throw ServerException("Error sending echo message back");                    
            }
        }
    }
}

