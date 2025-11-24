#include "LinuxConnection.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>



LinuxConnection::LinuxConnection(int socketFD,std::shared_ptr<MessageStore> messageStore):
  socketFD{socketFD},
  id{LinuxConnection::createId()},
  messageStore{messageStore},
  chunkSender{socketFD},
  currentState{LinuxConnection::ConnectionState::ACTIVE}
{};

int LinuxConnection::createId(){
    static int idCounter{0};
    return idCounter++; 
};


int LinuxConnection::getId() const{
    return id;
}; 

LinuxConnection::ConnectionState LinuxConnection::state() const{
    return currentState;
}; 
  

void LinuxConnection::addCommand(LinuxConnection::ConnectionRequest command){
   std::scoped_lock lock(mutex);
   commands.push(command);
}; 

void LinuxConnection::execute(LinuxConnection::ConnectionRequest command){
    switch(command){
        case ConnectionRequest::CLOSE:
          end();
        case ConnectionRequest::SEND:
          sendMessage();
    }
}


void LinuxConnection::end(){
    std::scoped_lock lock(mutex);
    close(socketFD);
    currentState = ConnectionState::CLOSED;
}

void LinuxConnection::sendMessage(){
    auto message = messageStore->retrieveMessageFromConnection(id);
    chunkSender.sendChunks(message.value());
}
void LinuxConnection::start(){

      while(currentState == ConnectionState::ACTIVE){
          //check if any message has been received
          auto receivedMessage = chunkSender.receiveChunks();
          if(receivedMessage.has_value()){
              messageStore->transmitMessageToUser(receivedMessage.value());
          }

          //execute the commands requested by the user
          std::scoped_lock lock(mutex);
          if(!this->commands.empty()){
              auto operation = commands.front();
              commands.pop();
              execute(operation); 
          }
      }
};
