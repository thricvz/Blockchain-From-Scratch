#pragma once
#include "NetworkComponents.hpp"
#include "../../CommunicationPack/Message.hpp"
#include <optional>

#include <queue>
#include <map>

using std::queue;
using std::map;

class MessageStore{
    public:
      MessageStore()=default;
      std::optional<Message> retrieveUserMessage();
      void transmitMessageToUser(const Message& message);      

      void transmitMessageToConnection(int connectionId,const Message& message);      
      std::optional<Message> retrieveMessageFromConnection(int connectionId);
    private:
      queue<Message> userMessages{};
      map<int,queue<Message>> connectionMessageStorage{};
};
