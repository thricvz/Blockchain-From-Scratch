#include "LinuxP2PNetworkImp.hpp" 
#include "SocketFunctionality.hpp"
#include <thread>
#include <iostream>
#include <exception>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <mutex>
#include <errno.h>


LinuxP2PNetworkImp::LinuxP2PNetworkImp(): messageStore{std::make_shared<MessageStore>()}{};

LinuxP2PNetworkImp::~LinuxP2PNetworkImp(){
  for(auto& [ip, connection] : activeConnections){
      this->endConnection(ip);
  }
}; 


void createNewConnections(std::weak_ptr<bool> parentObject ,LinuxP2PNetworkImp* imp,int listeningSocket){
    while(!parentObject.expired()){

        int neighborNodeSocket = accept(listeningSocket,NULL,NULL);   
        
        perror("failed to accept connection:");
        if(neighborNodeSocket !=-1){
            auto neighborAddress = getClientAddress(neighborNodeSocket);   
           

            //Doesn't accept two connections to a singular node
            if(!imp->connectionExists(neighborAddress)){


              auto messageStorePtr = imp->messageStore;
              auto neighborConnectionObject = std::make_unique<LinuxConnection>(neighborNodeSocket,messageStorePtr); 

              imp->addNeighbor(neighborAddress,std::move(neighborConnectionObject)); 
              imp->neighborNodes.push_back(neighborAddress);

            }else{
                close(neighborNodeSocket);
            }
        
        }
    }

};

void LinuxP2PNetworkImp::listenIncomingConnections(Port port) {
    try{
      int listeningSocketFD = setupSocket(IPV4Address{127,0,0,1},port,ConnectionDirection::INCOMING);



      acceptConnections = std::make_shared<bool>(true);
      
      std::thread listenerThread(createNewConnections,
          std::weak_ptr<bool>(acceptConnections),
          this,
          listeningSocketFD 
      );

      listenerThread.detach();
      

    }catch(std::exception& error){
      std::cout << error.what();
    }
}; 

inline void launchConnection(LinuxConnection* newConnection){
      newConnection->start();

}
void LinuxP2PNetworkImp::startConnection(const IPV4Address& destinationNode,Port port){
    if(connectionExists(destinationNode))
      return;

    try{
      int connectionSocketFD = setupSocket(destinationNode,port,ConnectionDirection::OUT_GOING);
      activeSockets[destinationNode] = connectionSocketFD; 

      std::unique_ptr<LinuxConnection> newConnection = std::make_unique<LinuxConnection>(connectionSocketFD,messageStore);
      std::thread connectionThread(launchConnection,newConnection.get());
      connectionThread.detach();

      activeConnections.insert({destinationNode,std::move(newConnection)});
      neighborNodes.push_back(destinationNode);

    }catch(std::exception &error){
        std::cout << error.what();
    }

}
void LinuxP2PNetworkImp::endConnection(const IPV4Address& neighbor){
     if(!connectionExists(neighbor))
       return;
         
     auto connection =  std::move(activeConnections[neighbor]);
     connection->addCommand(LinuxConnection::ConnectionRequest::CLOSE);
     
     if(connection->state() != LinuxConnection::ConnectionState::CLOSED){
        return endConnection(neighbor);
     }  

     connection = nullptr; 
     activeConnections.erase(neighbor); 
     neighborNodes.erase(std::find(neighborNodes.begin(),neighborNodes.end(),neighbor));
}

bool LinuxP2PNetworkImp::connectionExists(const IPV4Address& neighbor){
  return activeConnections.find(neighbor) != activeConnections.end();
}

void LinuxP2PNetworkImp::sendNeighbor(const IPV4Address& neighbor,const Message& message) {
    if(connectionExists(neighbor)){

       auto neighborConnection = activeConnections[neighbor].get();
       messageStore->transmitMessageToConnection(neighborConnection->getId(),message);
       neighborConnection->addCommand(LinuxConnection::ConnectionRequest::SEND);
    }
} 


void LinuxP2PNetworkImp::addNeighbor(const IPV4Address& neighbor,std::unique_ptr<LinuxConnection> connection){
   activeConnections[neighbor] = std::move(connection);
};

std::optional<Message> LinuxP2PNetworkImp::getLatestMessage() {
        return messageStore->retrieveUserMessage(); 
}; 
