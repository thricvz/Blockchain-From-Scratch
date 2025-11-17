#include "Message.hpp"


Message MessageCreator::generateMessage(){
  return Message{
    author,
    messageType,
    std::move(content), 
    std::move(flags) 
  };
};

MessageCreator& MessageCreator::addAuthor(const IPV4Address& author){
    this->author = author;
    return *this;
};

MessageCreator& MessageCreator::addContent(const vector<uint8_t>& content){
    this->content = content;
    return *this;
};

MessageCreator& MessageCreator::addFlag(Message::Flag flag){
   this->flags.push_back(flag);
   return *this;
};


MessageCreator& MessageCreator::addMessageType(Message::MessageType msgType){
  this->messageType = msgType;
  return *this;
};

