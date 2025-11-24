#include "ChunkSenderAndReceiver.hpp"
#include "../CommunicationPack/Serializer.hpp"
#include <sys/socket.h>
#include <cstdint>
#include <vector>

using std::uint8_t;

ChunkSenderAndReceiver::ChunkSenderAndReceiver(int socketFD):socketFD{socketFD}{};

void load_buffer(std::vector<uint8_t> &data,uint8_t buffer[],int bufferSize){
      int index = 0;
      while(!data.empty() && index < bufferSize){
        buffer[index] = data.front();
        data.erase(data.begin());
        index++;
      }

};
void  ChunkSenderAndReceiver::sendChunks(const Message& message){
      auto serializedMessage = Serializer::serialize(message);
      //calculate the number of chunks
      uint8_t numberOfChunks =  serializedMessage.size() / chunkSizeInBytes;
      
      uint8_t remainingData = serializedMessage.size() % chunkSizeInBytes;
      uint8_t amountDataLastChunk = (remainingData == 0) ? chunkSizeInBytes : remainingData;

      if ( remainingData != 0 )
        numberOfChunks++ ;
  

      //send the first message containing the amount of data
      uint8_t buffer[chunkSizeInBytes];
      buffer[0] = numberOfChunks; 
      buffer[1] = amountDataLastChunk;
      send(socketFD,buffer,chunkSizeInBytes,0);
      
      //send the serialized object
      int numberChunksLeft = numberOfChunks;
      while(numberChunksLeft > 0){
        load_buffer(serializedMessage,buffer,sizeof(buffer));
        send(socketFD,buffer,chunkSizeInBytes,0);
      }
};


static void copy_buffer(std::vector<uint8_t> &vec,uint8_t buffer[],int size){
        for(int index = 0; index < size; index++){
          vec.push_back(buffer[index]) ;
        }
};

std::optional<Message> ChunkSenderAndReceiver::receiveChunks(){
     uint8_t buffer[chunkSizeInBytes];
     bool firstPackageReceived = recv(socketFD,buffer,chunkSizeInBytes,0) > 0;
     if(!firstPackageReceived){
        return std::optional<Message>();
     }
     
     int numberOfChunksToReceive = static_cast<int>(buffer[0]);
     int sizeLastChunk = static_cast<int>(buffer[1]);
     std::vector<uint8_t> serializedMessage{};
     //retrieve all the data
     while(numberOfChunksToReceive !=0){
        if(recv(socketFD,buffer,chunkSizeInBytes,0) > 0){

           bool lastChunk = (numberOfChunksToReceive == 1);
           int sizeOfDataToCopy = lastChunk? sizeLastChunk : chunkSizeInBytes; 

           copy_buffer(serializedMessage,buffer,sizeOfDataToCopy);
           numberOfChunksToReceive --;
        }
     }
      
     auto receivedMessage = Serializer::deserialize(serializedMessage);
     return std::optional<Message>(receivedMessage);
};
