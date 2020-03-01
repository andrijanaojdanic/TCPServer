#ifndef __SERVER_EXCEPTION_HPP_
#define __SERVER_EXCEPTION_HPP_

#include <exception>
#include <string>

class ServerException: public std::exception {
    
    std::string errorMessage;

public:
    ServerException(std::string msg);

    const char* what() const throw();
};

#endif


