#include "P2PNetwork.hpp"
#include "LinuxP2PNetwork.hpp"
#include "LinuxP2PNetworkImp.hpp"


LinuxP2PNetwork::LinuxP2PNetwork(){
  imp = std::make_unique<LinuxP2PNetworkImp>();
  imp->listenIncomingConnections();
};

void LinuxP2PNetwork::startConnection(IPV4Address node){
    imp->startConnection(node);
};

void LinuxP2PNetwork::endConnection(IPV4Address neighbor){
    imp->endConnection(neighbor);
};

void LinuxP2PNetwork::propagateOnNetwork(Message message,vector<IPV4Address> excludeNodes){
    for (auto neighborNode : neighbors){
        if(std::find(neighbors.begin(),neighbors.end(),neighborNode) == neighbors.end())
          imp->sendNeighbor(neighborNode,message);
    }; 
};
void LinuxP2PNetwork::sendNeighbor(IPV4Address neighbor,Message message){
      imp->sendNeighbor(neighbor,message);
};
void LinuxP2PNetwork::onStartup(){
    ///reads the config file reads the address of the node and its port
};
