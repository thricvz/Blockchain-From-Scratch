#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include "include/LinuxP2PNetworkImp.hpp" 
#define DEFAULT_PORT 69



LinuxConnection::LinuxConnection(int socketFD):
  socketFD{socketFD}
{};

LinuxConnection::ExecutionState LinuxConnection::getCurrentState() const{
    return currentState;
}; 
  

void LinuxConnection::start(){
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
    hints->ai_flags = AI_PASSIVE;

    int errorCode = getaddrinfo(
        static_cast<string>(destinationNode).c_str(),
        "8080", //will be defined in the config file
        hints,
        &connectionData
    ); 

    auto cleanup = [&hints,&connectionData](){
       delete hints; 
       freeaddrinfo(connectionData); 
    };
    
    if(errorCode){
        std::cout << gai_strerror(errorCode);
        cleanup();
        throw std::runtime_error("Failed to get address info");
    }

    int socketFD = socket(connectionData->ai_family,connectionData->ai_socktype,connectionData->ai_protocol);  
    if(socketFD ==-1){
       cleanup();
       throw std::runtime_error("Failed to create socket for address:"+static_cast<string>(destinationNode));
    } 
    errorCode = connect(socketFD,connectionData->ai_addr,connectionData->ai_addrlen);
    if(errorCode){
       cleanup();
       close(socketFD);
       throw std::runtime_error("Failed to bind socket to address:"+static_cast<string>(destinationNode));
    }
    
    activeSockets.insert({destinationNode,socketFD});
    cleanup();
}

inline void launchConnection(LinuxConnection* newConnection){
      newConnection->start();

}
void LinuxP2PNetworkImp::startConnection(IPV4Address destinationNode){
    //only one connection is allowed for node
    if(activeConnections.find(destinationNode) != activeConnections.end())
      return;

    try{
      setupConnection(destinationNode);
      int connectionSocketFD = activeSockets[destinationNode]; 
      std::unique_ptr<LinuxConnection> newConnection = std::make_unique<LinuxConnection>(connectionSocketFD);
      std::thread connectionThread(launchConnection,newConnection.get());

      //connect to the socket 
     char secretMessage[55]  = "hello world! lets go network programming";
     send(connectionSocketFD,secretMessage,sizeof(secretMessage),0);

      activeConnections[destinationNode] = std::move(newConnection);
       
    }catch(std::exception &error){
        std::cout << error.what();
    }

}
void LinuxP2PNetworkImp::endConnection(IPV4Address neighbor){

}
void LinuxP2PNetworkImp::sendNeighbor(IPV4Address Neighbor,Message message) const{


} 





