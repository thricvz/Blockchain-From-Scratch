#include "P2PNetworkImp.hpp" 



class LinuxP2PNetworkImp : public P2PNetworkImp{
    public:
      LinuxP2PNetworkImp()= default; 
      virtual void startConnection(IPV4Address node) override;
      virtual void endConnection(IPV4Address neighbor) override;
      virtual void sendNeighbor(IPV4Address Neighbor,Message message) const override;

      virtual ~LinuxP2PNetworkImp()= default; 
}; 

