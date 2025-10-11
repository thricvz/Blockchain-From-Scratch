#pragma once
#include "NetworkComponents.hpp"
#include <map>
#include <vector>

using std::map;
using std::vector;

class P2PNetworkImp{
    public:
      P2PNetworkImp() = default;
      virtual void startConnection(IPV4Address node)=0;
      virtual void endConnection(IPV4Address neighbor)=0;
      virtual void sendNeighbor(IPV4Address Neighbor,Message message) const=0;

      vector<IPV4Address> neighborNodes{};
    private:
      map<IPV4Address,threadID> communicationChannel{};

};
