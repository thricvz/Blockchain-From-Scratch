#pragma once
#include <functional>
#include <memory>
#include <queue>      
#include <sys/socket.h>
#include <map>
#include "P2PNetworkImp.hpp" 
#include "NetworkComponents.hpp"

using std::queue;
using std::map;
using std::function;

class LinuxConnection{
  public:
    enum class ExecutionState{};
    enum class ExecutionCommand{SEND,CLOSE,PRINT};
    
    LinuxConnection(int socketFD);
    ExecutionState getCurrentState() const; 
    
    void start();  
    void execute(ExecutionCommand); 
    void addCommand(ExecutionCommand); 
  
  private:

    void commandPrint(){
        char message[]  = "this is some random message haheh";   
        send(socketFD,message,sizeof(message),0);
    }  
 
    int socketFD {};
    ExecutionState currentState{}; 
    queue<ExecutionCommand> commands{};        
};

class LinuxP2PNetworkImp : public P2PNetworkImp{
    public:

      LinuxP2PNetworkImp()= default; 
      virtual void startConnection(IPV4Address node) override;
      virtual void endConnection(IPV4Address neighbor) override;
      virtual void sendNeighbor(IPV4Address neighbor,Message message) override;
      
      bool connectionExists(IPV4Address neighbor);

     protected:
  
      virtual void setupConnection(IPV4Address destinationNode) ;
      map<IPV4Address,std::unique_ptr<LinuxConnection>> activeConnections{};
}; 

