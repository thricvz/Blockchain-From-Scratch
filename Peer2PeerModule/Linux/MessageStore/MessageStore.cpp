#include<MessageStore.hpp>

std::optional<Message> MessageStore::retrieveUserMessage(){
    if(userMessages.empty())
      return std::optional<Message>();   

    auto topMessage =  std::optional<Message>(userMessages .front()); 
    userMessages.pop();
    return topMessage;
};


void MessageStore::transmitMessageToUser(const Message& message){
    userMessages.push(message);
}

void MessageStore::transmitMessageToConnection(int connectionId,const Message& message){
   connectionMessageStorage[connectionId].push(message);
};      

std::optional<Message> MessageStore::retrieveMessageFromConnection(int connectionId){
    auto& storedMessages = connectionMessageStorage[connectionId]; 
    if(storedMessages.empty())
      return std::optional<Message>();   

    auto topMessage =  std::optional<Message>(storedMessages.front()); 
    storedMessages.pop();
    return topMessage;
};
