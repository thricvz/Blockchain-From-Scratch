#include <cstdint>
#include <vector>

using std::vector;
typedef std::uint8_t byte;

struct IPV4Address{
  byte firstByte{};
  byte secondByte{};
  byte thirdByte{};
  byte fourthByte{}; 
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
     vector<Flag> Flags{};
};
