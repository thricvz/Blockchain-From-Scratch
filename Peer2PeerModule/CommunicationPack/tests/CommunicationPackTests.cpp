#include <gtest/gtest.h>
#include "Message.hpp"
#include "Serializer.hpp"

TEST(Serialization,CompleteMessage) {
    auto originalMessage = 
      MessageCreator().addAuthor(IPV4Address{123,25,26,77})
      .addFlag(Message::Flag::REDIFFUSE)
      .addContent({12,65})
      .addMessageType(Message::MessageType::DISCOVERY)
      .generateMessage();
  
   auto deserializedMessage=Serializer::deserialize(Serializer::serialize(originalMessage));
   EXPECT_EQ(deserializedMessage,originalMessage);
};

TEST(Serialization,MessageMissingContent) {
    auto originalMessage = 
      MessageCreator().addAuthor(IPV4Address{255,4,53,45})
      .addFlag(Message::Flag::REDIFFUSE)
      .addMessageType(Message::MessageType::DISCOVERY)
      .generateMessage();
  
   auto deserializedMessage=Serializer::deserialize(Serializer::serialize(originalMessage));
   EXPECT_EQ(deserializedMessage,originalMessage);
};

TEST(Serialization,MessageMissingFlags) {
    auto originalMessage = 
      MessageCreator().addAuthor(IPV4Address{255,4,53,45})
      .addMessageType(Message::MessageType::DISCOVERY)
      .addContent({6,7,88,99})
      .generateMessage();
  
   auto deserializedMessage=Serializer::deserialize(Serializer::serialize(originalMessage));
   EXPECT_EQ(deserializedMessage,originalMessage);
};

TEST(Serialization,MultipleFlags) {
    auto originalMessage = 
      MessageCreator().addAuthor(IPV4Address{255,4,53,45})
      .addContent({34,23,34,33,88})      
      .addFlag(Message::Flag::REDIFFUSE)
      .addFlag(Message::Flag::REDIFFUSE)
      .addFlag(Message::Flag::REDIFFUSE)
      .addMessageType(Message::MessageType::DISCOVERY)
      .generateMessage();
  
   auto deserializedMessage=Serializer::deserialize(Serializer::serialize(originalMessage));
   EXPECT_EQ(deserializedMessage,originalMessage);
};

