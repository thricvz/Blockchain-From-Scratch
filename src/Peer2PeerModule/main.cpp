#include "LinuxP2PNetworkImp.hpp"
#include "NetworkComponents.hpp"
#include <memory>

int main(int argc, char **argv){
  IPV4Address serverIP{127,0,0,1}; 
  std::unique_ptr<LinuxP2PNetworkImp> imp = std::make_unique<LinuxP2PNetworkImp>();
  imp->startConnection(serverIP);
  imp->sendNeighbor(serverIP,{});  
  imp->sendNeighbor(serverIP,{});  
  
  return 0;
}
