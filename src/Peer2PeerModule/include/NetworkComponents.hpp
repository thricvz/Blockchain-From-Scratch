#include <cstdint>
#include <vector>

using std::vector;
typedef byte std::uint8_t;

struct IPV4Address{
  byte firstByte{};
  byte secondByte{};
  byte thirdByte{};
  bytes fourthByte{}; 
};


class Message{
   public:
      //Defines if the message concerns only the receiving node or is meant to be rediffused to the whole network
      enum class Flag{REDIFFUSE,DIRECT};

      vector<byte> getContent() const; 
      int getSize() const ;
      bool containsFlag(Flag) const ;
   private: 
     vector<byte> content{};
     IPV4Address Author{};
     vector<Flags> Flags{};
};
