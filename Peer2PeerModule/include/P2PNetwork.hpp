#pragma once
#include "NetworkComponents.hpp"
#include "P2PNetworkImp.hpp"
#include <memory>
#include <vector>

using std::vector;

class P2PNetwork{
  public:
    P2PNetwork()=default; 
    
    virtual void startConnection(IPV4Address node)=0;
    virtual void endConnection(IPV4Address neighbor)=0;
    
    virtual void propagateOnNetwork(Message message,vector<IPV4Address> excludeNodes={}) = 0;
    virtual void sendNeighbor(IPV4Address Neighbor,Message message) =0;
    virtual void onStartup() = 0;

    virtual ~P2PNetwork()=default;
    
    std::vector<IPV4Address> neighbors{};

  protected :
    std::unique_ptr<P2PNetworkImp> imp{nullptr}; 
    
};
