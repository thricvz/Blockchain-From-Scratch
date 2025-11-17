#pragma once
#include "IPV4Address.hpp" 
#include <cstdint>
#include <vector>

using std::vector;
using std::uint8_t;
using byte = std::uint8_t;

struct Message{
    enum class Flag : uint8_t {REDIFFUSE,DIRECT};
    enum class MessageType : uint8_t {DISCOVERY};

    IPV4Address author{};
    MessageType messageType {};
    vector<byte> content{};
    vector<Flag> flags{};
      
    bool operator==(const Message& m2) const{
        return (this->author == m2.author) &&
          (this->messageType == m2.messageType) &&
          (this->flags == m2.flags) &&
          (this->content == m2.content);
    } 
};

class MessageCreator{
  public:
    Message generateMessage();
    MessageCreator& addAuthor(const IPV4Address&);
    MessageCreator& addContent(const vector<uint8_t>&);
    MessageCreator& addFlag(Message::Flag);
    MessageCreator& addMessageType(Message::MessageType);
  
  private: 
    IPV4Address author{};
    Message::MessageType messageType {};
    vector<byte> content{};
    vector<Message::Flag> flags{};
};

