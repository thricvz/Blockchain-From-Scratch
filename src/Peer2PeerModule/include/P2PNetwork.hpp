#include "NetworkComponents.hpp"
#include "P2PNetworkImp.hpp"
#include <memory>
#include <vector>

using std::vector;
class P2PNetwork{
  public:
    P2PNetwork()=default; 
    
    void startConnection(IPV4Address node);
    void endConnection(IPV4Address neighbor);

    void propagateOnNetwork(Message message,vector<IPV4Address> excludeNodes={}) const;
    void sendNeighbor(IPV4Address Neighbor,Message message) const;
    virtual void onStartup() const  = 0;

    virtual ~P2PNetwork()=default;
  private :
    std::unique_ptr<P2PNetworkImp> networkInterface{nullptr}; 

};
