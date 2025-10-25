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
  

void LinuxConnection::addCommand(LinuxConnection::ExecutionCommand command){
   commands.push(command);
}; 

void LinuxConnection::execute(LinuxConnection::ExecutionCommand command){
    switch(command){
        case ExecutionCommand::PRINT:
          commandPrint();
        default:
          ;
    }
}

void LinuxConnection::start(){

      while(true){
          if(this->commands.empty())
            continue;
          
          auto operation = commands.front();
          commands.pop();
          
          execute(operation); 
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
    if(connectionExists(destinationNode))
      return;

    try{
      setupConnection(destinationNode);
      int connectionSocketFD = activeSockets[destinationNode]; 
      std::unique_ptr<LinuxConnection> newConnection = std::make_unique<LinuxConnection>(connectionSocketFD);
      std::thread connectionThread(launchConnection,newConnection.get());
      connectionThread.detach();
      //connect to the socket 

      activeConnections.insert({destinationNode,std::move(newConnection)});
       
    }catch(std::exception &error){
        std::cout << error.what();
    }

}
void LinuxP2PNetworkImp::endConnection(IPV4Address neighbor){

}

bool LinuxP2PNetworkImp::connectionExists(IPV4Address neighbor){
  return activeConnections.find(neighbor) != activeConnections.end();
}

void LinuxP2PNetworkImp::sendNeighbor(IPV4Address neighbor,Message message) {
    if(connectionExists(neighbor)){
       activeConnections[neighbor]->execute(LinuxConnection::ExecutionCommand::PRINT);
    }
} 




