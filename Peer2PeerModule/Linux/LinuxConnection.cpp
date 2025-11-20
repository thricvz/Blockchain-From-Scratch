#include "LinuxConnection.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


LinuxConnection::LinuxConnection(int socketFD,std::shared_ptr<MessageStore> messageStore):
  socketFD{socketFD},
  currentState{LinuxConnection::ConnectionState::ACTIVE},
  messageStore{messageStore},
  id{LinuxConnection::createId()}
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
   commands.push(command);
}; 

void LinuxConnection::execute(LinuxConnection::ConnectionRequest command){
    switch(command){
        case ConnectionRequest::CLOSE:
          end();
    }
}


void LinuxConnection::end(){
    close(socketFD);
    currentState = ConnectionState::CLOSED;
}
void LinuxConnection::start(){

      while(currentState == ConnectionState::ACTIVE){
          //first check if any message was received 
          if(this->commands.empty())
            continue;
          
          auto operation = commands.front();
          commands.pop();
          
          execute(operation); 
      }
};
