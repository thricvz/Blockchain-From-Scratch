#include "P2PNetwork.hpp"
#include <algorithm>
#include "nlohmann/json.hpp"

//using json = nlohmann::json;
//using basic_json = nlohmann::basic_json;

P2PNetwork::P2PNetwork(std::unique_ptr<P2PNetworkImp> platformImp,const std::string& configurationFile): 
  imp{std::move(platformImp)}, config{configurationFile}
{
  imp->listenIncomingConnections(config.getListeningPort()); 

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

void P2PNetwork::onStartup(){
    ///reads the config file reads the address of the node and its port
};
