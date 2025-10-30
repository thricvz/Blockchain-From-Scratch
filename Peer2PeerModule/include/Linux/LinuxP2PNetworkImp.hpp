#pragma once
#include <functional>
#include <memory>
#include <map>

#include "P2PNetworkImp.hpp" 
#include "LinuxConnection.hpp"
#include "NetworkComponents.hpp"

class LinuxP2PNetworkImp : public P2PNetworkImp{
    public:

      LinuxP2PNetworkImp()=default; 
      ~LinuxP2PNetworkImp(); 

      virtual void startConnection(IPV4Address node) override;
      virtual void endConnection(IPV4Address neighbor) override;
      virtual void sendNeighbor(IPV4Address neighbor,Message message) override;
      virtual void listenIncomingConnections() override;

      bool connectionExists(IPV4Address neighbor);
      void addNeighbor(const IPV4Address& neighbor,std::unique_ptr<LinuxConnection> connection);
     protected:
  
      map<IPV4Address,std::unique_ptr<LinuxConnection>> activeConnections{};
    
     private:
      std::shared_ptr<bool> acceptConnections{nullptr};
}; 

