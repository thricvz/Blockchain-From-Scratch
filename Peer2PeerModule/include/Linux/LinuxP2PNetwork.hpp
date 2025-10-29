#pragma once
#include "P2PNetwork.hpp"

class LinuxP2PNetwork : public P2PNetwork{
  public:
    LinuxP2PNetwork(); 

    virtual void startConnection(IPV4Address node) override;
    virtual void endConnection(IPV4Address neighbor) override;

    virtual void propagateOnNetwork(Message message,vector<IPV4Address> excludeNodes={})  override;
    virtual void sendNeighbor(IPV4Address Neighbor,Message message) override;
    virtual void onStartup() override;
};
