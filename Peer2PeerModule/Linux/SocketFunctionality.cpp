#include "SocketFunctionality.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <utility>
#include <memory>
#include <stdexcept>


#define MAX_CLIENT_QUEUE_LENGTH 3
using std::pair;
using std::unique_ptr;
using socketFD = int;



pair<socketFD,unique_ptr<addrinfo*>> createSocket(const IPV4Address& address,Port port){
    unique_ptr<addrinfo> hints;
    unique_ptr<addrinfo*> connectionDataPtr;

    connectionDataPtr = std::make_unique<addrinfo*>(); 
    hints = std::make_unique<addrinfo>(); 

    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    int errorCode = getaddrinfo(
        static_cast<string>(address).c_str(),
        port, 
        hints.get(),
        connectionDataPtr.get()
    ); 
    
    if(errorCode){
        throw std::runtime_error("Failed to get address info");
    }

    auto connectionData = *connectionDataPtr.get();
    int socketFD = socket(connectionData->ai_family,connectionData->ai_socktype,connectionData->ai_protocol);  

    if(socketFD ==-1){
       throw std::runtime_error("Failed to create socket for address:"+static_cast<string>(address));
    } 

    
    return std::pair(socketFD,std::move(connectionDataPtr));


};

int setupSocket(const IPV4Address& address,Port port,ConnectionDirection connectionType){
    try{
      auto results = createSocket(address,port); 
      int socketFD = results.first;
      auto connectionData = *results.second.get();
      
      
      switch(connectionType){
          case ConnectionDirection::INCOMING:
              bind(socketFD,connectionData->ai_addr,connectionData->ai_addrlen); 
              listen(socketFD,MAX_CLIENT_QUEUE_LENGTH);
              break;

          case ConnectionDirection::OUT_GOING:
              connect(socketFD,connectionData->ai_addr,connectionData->ai_addrlen); 
              break;

      }
      return socketFD;
    }catch(std::exception&  error){
        throw error;
    }
};
