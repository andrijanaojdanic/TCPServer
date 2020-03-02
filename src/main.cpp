#include <iostream>
#include "TCPServer.hpp"

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



