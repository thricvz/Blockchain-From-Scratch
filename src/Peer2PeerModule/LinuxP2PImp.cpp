#include <thread>
#include <iostream>
#include <exception>
#include <sys/socket.h>
#include "include/LinuxP2PNetworkImp.hpp" 
#define DEFAULT_PORT 69



LinuxConnection::LinuxConnection(IPV4Address destinationNode){
    this->destinationNode = destinationNode; 
};

LinuxConnection::ExecutionState LinuxConnection::getCurrentState() const{
    return currentState;
}; 
  
void LinuxConnection::create(){
};

void LinuxConnection::launch(){
      //connect to the socket 
      while(true){
          if(this->commands.empty())
            continue;
          
          auto operation = commands.front();
          commands.pop();
          commandFunctions[operation](); 
          
      }
};
void LinuxP2PNetworkImp::setupConnection(IPV4Address destinationNode){
    //create a socket for the connection right here
    addrinfo saddrinfo,*hints,*connectionData;
    hints = new addrinfo(); 
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;


    int errorCode = getaddrinfo(
        static_cast<string>(destinationNode).c_str(),
        NULL, //will be defined in the config file
        hints,
        &connectionData
    ); 

    auto cleanup = [hints,connectionData](){
       delete hints; 
       freeaddrinfo(connectionData); 
    };
    
    if(errorCode){
        std::cout << gai_strerror(errorCode);
        cleanup();
        throw std::runtime_error("Failed to get address info");
    }
    //creating socket
    int socketFD = socket(connectionData->ai_family,connectionData->ai_socktype,connectionData->ai_protocol);  
    if(socketFD ==-1){
       cleanup();
       throw std::runtime_error("Failed to create socket for address:"+static_cast<string>(destinationNode));
    } 
    errorCode = connection(socketFD,connectionData->ai_addr,connectionData->ai_addrlen);
    if(errorCode){
       cleanup();
       throw std::runtime_error("Failed to bind socket to address:"+static_cast<string>(destinationNode));
    }
    
    threadInfo newConnection(0,socketFD);
    communicationChannel[destinationNode] = newConnection;
    cleanup();
}

void LinuxP2PNetworkImp::startConnection(IPV4Address destinationNode){
    try{
      setupConnection(destinationNode);

    }catch(Exception error){
        std::cout << error.what();
    }

}
void LinuxP2PNetworkImp::endConnection(IPV4Address neighbor){

}
void LinuxP2PNetworkImp::sendNeighbor(IPV4Address Neighbor,Message message) const{


} 




