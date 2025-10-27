#include "include/LinuxP2PNetworkImp.hpp" 
#include "SocketFunctionality.hpp"
#include <thread>
#include <iostream>
#include <exception>


LinuxP2PNetworkImp::~LinuxP2PNetworkImp(){
  for(auto& [ip, connection] : activeConnections){
      this->endConnection(ip);
  }
}; 


void createNewConnections(std::weak_ptr<bool> keepListening ,LinuxP2PNetworkImp* imp,int listeningSocket){


};

void LinuxP2PNetworkImp::listenIncomingConnections() {
    try{
      //bind the socket
      int listeningSocketFD = setupSocket(IPV4Address{127,0,0,1},"8001");

      acceptConnections = std::make_shared<bool>(true);
      
      std::thread listenerThread(createNewConnections,
          std::weak_ptr<bool>(acceptConnections),
          this,
          listeningSocketFD, 
      )

    }catch(std::exception& error){
      std::cout << error.what();
    }
}; 

inline void launchConnection(LinuxConnection* newConnection){
      newConnection->start();

}
void LinuxP2PNetworkImp::startConnection(IPV4Address destinationNode){
    //only one connection is allowed for node
    if(connectionExists(destinationNode))
      return;

    try{
      //creates the socket for the onnection
      int connectionSocketFD = setupSocket(destinationNode,"8080");
      activeSockets[destinationNode] = connectionSocketFD; 

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
     if(!connectionExists(neighbor))
       return;
         
     auto connection =  std::move(activeConnections[neighbor]);
     connection->execute(LinuxConnection::ConnectionRequest::CLOSE);
     
     //wait for the connection 
     if(connection->state() != LinuxConnection::ConnectionState::CLOSED){
        return endConnection(neighbor);
     }  
     connection = nullptr; 
     activeConnections.erase(neighbor); 
}

bool LinuxP2PNetworkImp::connectionExists(IPV4Address neighbor){
  return activeConnections.find(neighbor) != activeConnections.end();
}

void LinuxP2PNetworkImp::sendNeighbor(IPV4Address neighbor,Message message) {
    if(connectionExists(neighbor)){
       activeConnections[neighbor]->execute(LinuxConnection::ConnectionRequest::SEND);
    }
} 




