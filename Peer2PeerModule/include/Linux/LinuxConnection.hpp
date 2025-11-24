#pragma once
#include "MessageStore/MessageStore.hpp"
#include "ChunkSenderAndReceiver.hpp"
#include <queue>
#include <memory>
#include <mutex>

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
    void sendMessage();    

 
    int socketFD {};
    int id{};

    std::shared_ptr<MessageStore> messageStore;
    ChunkSenderAndReceiver chunkSender;
    ConnectionState currentState{}; 

    queue<ConnectionRequest> commands{};        
    std::mutex mutex{};
};

