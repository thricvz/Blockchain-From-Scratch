#pragma once
#include "IPV4Address.hpp" 
#include <cstdint>
#include <vector>

using std::vector;
using std::uint8_t;
using byte = std::uint8_t;

struct Message{
    enum class Flag : uint8_t {REDIFFUSE,DIRECT};
    enum class MessageType : uint8_t {};

    IPV4Address author{};
    uint8_t messageType {};
    vector<byte> content{};
    vector<Flag> flags{};
};

class MessageCreator{
  public:
    Message generateMessage();
    MessageCreator& addAuthor(const IPV4Address&);
    MessageCreator& addContent(const vector<uint8_t>&);
    MessageCreator& addFlag(Message::Flag);
    MessageCreator& addMessageType(uint8_t);
  
  private: 
    IPV4Address author{};
    uint8_t messageType {};
    vector<byte> content{};
    vector<Flag> flags{};
};

