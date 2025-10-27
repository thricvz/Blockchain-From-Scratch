#pragma once
#include <queue>

using std::queue;

class LinuxConnection{
  public:
    enum class ConnectionState{CLOSED,ACTIVE};
    enum class ConnectionRequest{SEND,CLOSE};
    
    LinuxConnection(int socketFD);
    ConnectionState state() const; 
    
    void start();  
    void execute(ConnectionRequest); 
    void addCommand(ConnectionRequest); 
  
  private:

    void end();
 
    int socketFD {};
    ConnectionState currentState{}; 
    queue<ConnectionRequest> commands{};        
};

