#include "P2PNetwork.hpp"
#include <algorithm>
#include "nlohmann/json.hpp"


P2PNetwork::P2PNetwork(std::unique_ptr<P2PNetworkImp> platformImp,const std::string& listeningPort): 
  imp{std::move(platformImp)}
{
  imp->listenIncomingConnections(listeningPort); 

};

void P2PNetwork::startConnection(const IPV4Address& node){
    imp->startConnection(node);
};

void P2PNetwork::endConnection(const IPV4Address& neighbor){
    imp->endConnection(neighbor);
};

void P2PNetwork::propagateOnNetwork(const Message& message,vector<IPV4Address> excludeNodes){
    for (auto neighborNode : neighbors){
        if(std::find(neighbors.begin(),neighbors.end(),neighborNode) == neighbors.end())
          imp->sendNeighbor(neighborNode,message);
    }; 
};
void P2PNetwork::sendNeighbor(const IPV4Address& neighbor,const Message& message){
      imp->sendNeighbor(neighbor,message);
};


std::optional<Message> P2PNetwork::getLatestMessage(){
    return imp->getLatestMessage();
}; 
