#pragma once
#include "NetworkComponents.hpp"
#include "P2PNetworkImp.hpp"
#include <memory>
#include <vector>
#include <string>
#include <optional>

using std::vector;

class P2PNetwork{
  public:
    
    P2PNetwork(std::unique_ptr<P2PNetworkImp>,const std::string& listeningPort);
   


    void startConnection(const IPV4Address& node);
    void endConnection(const IPV4Address& neighbor);
    
    void propagateOnNetwork(const Message& message,vector<IPV4Address> excludeNodes={});
    void sendNeighbor(const IPV4Address& Neighbor,const Message& message);

    std::optional<Message> getLatestMessage(); 

    vector<IPV4Address> getNeighbors(){
        return imp->neighborNodes;
    }

    ~P2PNetwork()=default;
    
    std::vector<IPV4Address> neighbors{};

  private:
    std::unique_ptr<P2PNetworkImp> imp{nullptr}; 
};
