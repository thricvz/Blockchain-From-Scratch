#include "Serializer.hpp"


vector<uint8_t> Serializer::serialize(const Message& message){
    vector<uint8_t> encodedMessage{};   

    encodedMessage.push_back(message.author.firstByte);
    encodedMessage.push_back(message.author.secondByte);
    encodedMessage.push_back(message.author.thirdByte);
    encodedMessage.push_back(message.author.fourthByte);

    encodedMessage.push_back(static_cast<uint8_t>(message.messageType));

    uint8_t numberFlags = message.flags.size();
    encodedMessage.push_back(numberFlags);

    for( auto flag : message.flags){
      encodedMessage.push_back(static_cast<uint8_t>(flag));
    } 


    encodedMessage.insert(
      encodedMessage.end(),
      message.content.begin(),
      message.content.end()
    );
    return encodedMessage;
};

Message Serializer::deserialize(vector<uint8_t> byteStream){
     Message extractedMessage{};
     extractedMessage.author = IPV4Address{byteStream[0],
        byteStream[1],
        byteStream[2],
        byteStream[3]}; 

    extractedMessage.messageType = static_cast<Message::MessageType>(byteStream[4]);
    
    //reading variable length information
    auto readIterator = byteStream.begin()+5;
    int nFlags = *readIterator;
    
    readIterator++; 
    for(int i = 0; i < nFlags; i ++){
        extractedMessage.flags.push_back(static_cast<Message::Flag>(*readIterator));
        readIterator++;
    }
    
    while(readIterator != byteStream.end()){
        extractedMessage.content.push_back(*readIterator);
        readIterator++;

    };

    return extractedMessage; 
};
