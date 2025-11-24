#include<MessageStore.hpp>

std::optional<Message> MessageStore::retrieveUserMessage(){
    std::scoped_lock lock(mutex);
    if(userMessages.empty())
      return std::optional<Message>();   

    auto topMessage =  std::optional<Message>(userMessages .front()); 
    userMessages.pop();
    return topMessage;
};


void MessageStore::transmitMessageToUser(const Message& message){
    std::scoped_lock lock(mutex);
    userMessages.push(message);
}

void MessageStore::transmitMessageToConnection(int connectionId,const Message& message){
   std::scoped_lock lock(mutex);
   connectionMessageStorage[connectionId].push(message);
};      

std::optional<Message> MessageStore::retrieveMessageFromConnection(int connectionId){
    std::scoped_lock lock(mutex);
    auto& storedMessages = connectionMessageStorage[connectionId]; 
    if(storedMessages.empty())
      return std::optional<Message>();   

    auto topMessage =  std::optional<Message>(storedMessages.front()); 
    storedMessages.pop();
    return topMessage;
};
