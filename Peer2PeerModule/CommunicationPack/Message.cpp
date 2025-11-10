#include "Message.hpp"

Message& Message::addAuthor(const IPV4Address& author){
    this->author = author;
    return this;
};

Message& Message::addContent(const vector<uint8_t>& content){
    this->content = content;
    return this;
};

Message& Message::addFlag(Message::Flag flag){
   this->flags.push_back(flag);
   return this;
};

Message& Message::addType(Message::MessageType type){
   this->type = type;
   return this;
};


