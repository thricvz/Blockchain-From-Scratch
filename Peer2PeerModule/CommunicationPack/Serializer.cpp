#pragma once
#include "Serializer.hpp"


vector<uint8_t> Serializer::serialize(const Message& message){
    vector<uint8_t> encodedMessage{};   

    encodedMessage.push_back(message.author.firstByte);
    encodedMessage.push_back(message.author.secondByte);
    encodedMessage.push_back(message.author.thirdByte);
    encodedMessage.push_back(message.author.fourthByte);

    uint8_t numberFlags = message.flags.size();
    encodedMessage.push_back(numberFlags);

    for( auto flag : flags){
      encodedMessage.push_back(static_cast<uint8_t>(flag));
    } 

    encodedMessage.push_back(message.messageType);

    encodedMessage.insert(
      encodedMessage.end(),
      message.content.begin(),
      message.content.end()
    );
};

Message Serializer::deserialize(vector<uint8_t> byteStream){
    ;

};
