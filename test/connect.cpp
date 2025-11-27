
#include "P2PNetwork.hpp"
#include "Linux/LinuxP2PNetworkImp.hpp"
#include "Linux/LinuxP2PNetworkImp.hpp"

int main(){
  
  P2PNetwork netOut{std::make_unique<LinuxP2PNetworkImp >(),"8080"};
  IPV4Address otherNodeAddress{122,0,0,4};
  auto messageToSend = MessageCreator()
        .addContent({00,11,22,33})
        .generateMessage();

  netOut.startConnection(otherNodeAddress,"8081");
  netOut.sendNeighbor(otherNodeAddress,Message{});

  return 0;
};
