#pragma once
#include "NetworkComponents.hpp"
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <optional>

using std::map;
using std::vector;
using std::pair;
using std::queue;

using socketFD = int;

class P2PNetworkImp{
    public:
      P2PNetworkImp() = default;
      virtual void endConnection(const IPV4Address& neighbor)=0;
      virtual void sendNeighbor(const IPV4Address& Neighbor,const Message& message)=0;
      virtual void startConnection(const IPV4Address& node,Port port)=0;
      virtual void listenIncomingConnections(Port port) = 0;
      
      virtual std::optional<Message> getLatestMessage() = 0;
      virtual ~P2PNetworkImp()=default;
   
      vector<IPV4Address> neighborNodes{};

    protected:
      map<IPV4Address,socketFD> activeSockets{};

};
