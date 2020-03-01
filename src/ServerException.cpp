#include "ServerException.hpp"

ServerException::ServerException(std::string msg):errorMessage(msg){}

const char* ServerException::what() const throw(){
    return errorMessage.c_str();
}
