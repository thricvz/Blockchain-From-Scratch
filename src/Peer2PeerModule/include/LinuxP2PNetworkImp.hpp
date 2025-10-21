#pragma once
#include <functional>
#include <queue>      
#include <map>
#include "P2PNetworkImp.hpp" 
#include "NetworkComponents.hpp"

using std::queue;
using std::map;
using std::function;

class LinuxConnection{
  public:
    enum class ExecutionState{};
    enum class ExecutionCommand{SEND,CLOSE};
    
    LinuxConnection(IPV4Address destinationNode);
    ExecutionState getCurrentState() const; 
  
    void launch();
  private:
    using commandFunction = function<void()>; 
    inline static map<ExecutionCommand,commandFunction> commandFunctions{};
    
    int socketFD {};
    ExecutionState currentState{}; 
    queue<ExecutionCommand> commands{};        
};

class LinuxP2PNetworkImp : public P2PNetworkImp{
    public:
      LinuxP2PNetworkImp()= default; 
      virtual void startConnection(IPV4Address node) override;
      virtual void endConnection(IPV4Address neighbor) override;
      virtual void sendNeighbor(IPV4Address Neighbor,Message message) const override;

      virtual ~LinuxP2PNetworkImp()= default; 

    protected:
      virtual void setupConnection(IPV4Address node) override;
}; 

