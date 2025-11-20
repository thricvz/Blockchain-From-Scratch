#pragma once
#include "MessageStore/MessageStore.hpp"
#include <queue>
#include <memory>

using std::queue;

class LinuxConnection{
  public:
    static int createId();
    enum class ConnectionState{CLOSED,ACTIVE};
    enum class ConnectionRequest{SEND,CLOSE};
    
    LinuxConnection(int socketFD,std::shared_ptr<MessageStore> messageStore);
    ConnectionState state() const; 
    
    void start();  
    void execute(ConnectionRequest); 
    void addCommand(ConnectionRequest); 
    
    int getId() const;  

  private:

    void end();
 
    int socketFD {};
    int id{};

    ConnectionState currentState{}; 
    queue<ConnectionRequest> commands{};        
    std::shared_ptr<MessageStore> messageStore;
};

