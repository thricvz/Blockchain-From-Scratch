#pragma once
#include "../CommunicationPack/Message.hpp"
#include <optional>

class ChunkSenderAndReceiver{
    static int inline chunkSizeInBytes{32};
    public:
      ChunkSenderAndReceiver(int socketFD);

      void  sendChunks(const Message& message);
      std::optional<Message> receiveChunks();

    private:
      int socketFD;
};
