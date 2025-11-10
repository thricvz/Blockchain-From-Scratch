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

      virtual void startConnection(const IPV4Address& node) override;
      virtual void endConnection(const IPV4Address& neighbor) override;
      virtual void sendNeighbor(const IPV4Address& neighbor,const Message& message) override;
      virtual void listenIncomingConnections() override;

      bool connectionExists(const IPV4Address& neighbor);
      void addNeighbor(const IPV4Address& neighbor,std::unique_ptr<LinuxConnection> connection);
     protected:
  
      map<IPV4Address,std::unique_ptr<LinuxConnection>> activeConnections{};
    
     private:
      std::shared_ptr<bool> acceptConnections{nullptr};
}; 

