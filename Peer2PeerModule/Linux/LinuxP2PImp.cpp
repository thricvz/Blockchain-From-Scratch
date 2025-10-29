#include "LinuxP2PNetworkImp.hpp" 
#include "SocketFunctionality.hpp"
#include <thread>
#include <iostream>
#include <exception>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

LinuxP2PNetworkImp::~LinuxP2PNetworkImp(){
  for(auto& [ip, connection] : activeConnections){
      this->endConnection(ip);
  }
}; 


void createNewConnections(std::weak_ptr<bool> parentObject ,LinuxP2PNetworkImp* imp,int listeningSocket){
    while(!parentObject.expired()){

        sockaddr *incomingNode{nullptr};
        socklen_t *incomingNodeAddrlength{};
        auto incomingNodeSocket = accept(listeningSocket,incomingNode,incomingNodeAddrlength);   

        if(incomingNodeSocket ==-1){
          std::cout << "failed to get new connection";
          return;
        }
        
        std::cout << "new node connected to us" << incomingNodeSocket << "\n";  
        //create new LinuxConnection
    }

};

void LinuxP2PNetworkImp::listenIncomingConnections() {
    try{
      //bind the socket
      int listeningSocketFD = setupSocket(IPV4Address{127,0,0,1},"8001",ConnectionDirection::INCOMING);

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
void LinuxP2PNetworkImp::startConnection(IPV4Address destinationNode){
    //only one connection is allowed for node
    if(connectionExists(destinationNode))
      return;

    try{
      //creates the socket for the onnection
      int connectionSocketFD = setupSocket(destinationNode,"8080",ConnectionDirection::OUT_GOING);
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




