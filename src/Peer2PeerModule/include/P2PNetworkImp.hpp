#pragma once
#include "NetworkComponents.hpp"
#include <map>
#include <vector>
#include <utility>
using std::map;
using std::vector;
using std::pair;

using socketFD = int;

class P2PNetworkImp{
    public:
      P2PNetworkImp() = default;
      virtual void endConnection(IPV4Address neighbor)=0;
      virtual void sendNeighbor(IPV4Address Neighbor,Message message)=0;
      virtual void startConnection(IPV4Address node)=0;
      virtual ~P2PNetworkImp()=default;
   
      vector<IPV4Address> neighborNodes{};

    protected:
      virtual void setupConnection(IPV4Address node)=0;
      map<IPV4Address,socketFD> activeSockets{};
      

};
