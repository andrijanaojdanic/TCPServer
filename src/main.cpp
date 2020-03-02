#include <iostream>
#include "TCPServer.hpp"

constexpr static int DEFAULT_PROTOCOL = 0;
constexpr static int RECV_BUF_SZ = 1024;

int main()
{
    TCPServer tcpServer =  TCPServer();
    
    try{
        tcpServer.initServer();
        
        while(true)
        {
            tcpServer.acceptConnection(); 
            tcpServer.receiveMessage(); 
        }
  
    }
    catch(ServerException e){
        std::cout << e.what() << std::endl;
    }

	return 0;
}


/*
int serverSocketFd = 0;
    struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port   = htons(5000), // htons = Host To Network Short, makes sure that bytes are stored in network data order
                                                // Short because it works only on 16b integers
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // htonl = Host To Network Long, works with 32b integers

    struct sockaddr clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int msgSize = 0;    // in number of bytes
    int clientSocketFd = 0;

    char recv_buffer[RECV_BUF_SZ];

	// Create socket
    serverSocketFd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);    
    if (serverSocketFd < 0)
    { 
        perror("Error creating socket");
    }
    else
    {
        // Bind socket to inet addr
        if (bind(serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
        {
            perror("Error binding socket");
        }
        else
        {
            // Put socket in server mode - listen to connections
            listen(serverSocketFd,1);

            std::cout << "Waiting for connection..." << std::endl;

            while (true)
            {
                // Accept connection
                clientSocketFd = accept(serverSocketFd, &clientAddress, &clientAddressLen);
                if (clientSocketFd < 0)
                {
                    perror("Error accepting connection");
                    break;
                }
                else
                {
                    while (true)
                    {
                        std::cout << "Connection from " << clientAddress.sa_data << std::endl;
                        // Receive end echo messages
                        msgSize = recv(clientSocketFd, recv_buffer, RECV_BUF_SZ, 0);
                        if (msgSize > 0)
                        {l
                            std::cout << recv_buffer << std::endl;
                            if (!send(clientSocketFd, recv_buffer, msgSize, 0))
                            {
                                perror("Error sending message");
                                break;
                            }
                        }
                        else 
                        {
                            std::cout << "Connection with " << clientAddress.sa_data << "terminated." << std::endl;
                            close(clientSocketFd);
                            break;
                        }
                    }
                    
                }
            }
        }
    }



*/


