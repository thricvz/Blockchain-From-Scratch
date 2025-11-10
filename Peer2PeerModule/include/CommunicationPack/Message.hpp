#pragma once
#include "IPV4Address.hpp" 
#include <cstdint>
#include <vector>

using std::vector;
using std::uint8_t;

class Serializer;

class Message{
   public:
      //Defines if the message concerns only the receiving node or is meant to be rediffused to the whole network
    enum class Flag : uint8_t {REDIFFUSE,DIRECT};
    enum class MessageType : uint8_t {};

    Message() = default;
    
    Message& addAuthor(const IPV4Address&);
    Message& addContent(const vector<uint8_t>&);
    Message& addFlag(Flag);
    Message& addType(MessageType);

    friend class Serializer; 

   private: 
    
     IPV4Address author{};
     vector<byte> content{};
     vector<Flag> flags{};
     MessageType type{}; 
};
