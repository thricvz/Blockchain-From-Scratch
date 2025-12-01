#include "SocketFunctionality.hpp"
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <utility>
#include <memory>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <cmath>
#include <cstring>
#include <errno.h>

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
    int socketFD = socket(connectionData->ai_family,connectionData->ai_socktype ,connectionData->ai_protocol);  

    if(socketFD ==-1){
       throw std::runtime_error("Failed to create socket for address:"+static_cast<string>(address));
    } 

    
    return std::pair(socketFD,std::move(connectionDataPtr));


};

int setupSocket(const IPV4Address& address,Port port,ConnectionDirection connectionType){
    try{
      /*
        use a structred binding
        auto [socketFD,connectionData] = createSocket(address,port);
      */
      auto results = createSocket(address,port); 
      int socketFD = results.first;
      auto connectionData = *results.second.get();

      
      auto checkForCleanup = [](int socket,int operationResult)-> void {
               if(operationResult==-1){
                  close(socket);  
                  throw std::runtime_error("Failed to bind/connect the socket\n");
               } 
      };  
      int bindResult{};

      switch(connectionType){
          case ConnectionDirection::INCOMING:
              bindResult = bind(socketFD,connectionData->ai_addr,connectionData->ai_addrlen); 
              checkForCleanup(socketFD,bindResult);
              break;

          case ConnectionDirection::OUT_GOING:
              bindResult = connect(socketFD,connectionData->ai_addr,connectionData->ai_addrlen); 
              perror("Failed to connect due to:");
              checkForCleanup(socketFD,bindResult);
              break;

      }
      return socketFD;
    }catch(std::exception&  error){
        throw error;
    }
};

IPV4Address getClientAddress(int clientSocket){
    struct sockaddr_in serv_addr; 
    socklen_t len; 

    memset(&serv_addr, '0', sizeof(serv_addr));
    getpeername(clientSocket, (struct sockaddr*)&serv_addr, &len );
  
    return charToAddress(inet_ntoa(serv_addr.sin_addr));
};


