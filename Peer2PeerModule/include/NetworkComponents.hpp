#pragma once
#include <cstdint>
#include <vector>
#include <string>

using std::vector;
using std::to_string;
using std::string;
using byte = std::uint8_t;

struct IPV4Address{
  byte firstByte{};
  byte secondByte{};
  byte thirdByte{};
  byte fourthByte{}; 
  
  operator string() const {
      return (
          to_string(firstByte) +
          '.' + to_string(secondByte)+
          '.' + to_string(thirdByte)+
          '.' + to_string(fourthByte)
          );
    } 
  
 
  bool operator<(const IPV4Address& rhs) const{
      return this->calcComparisonValue() < rhs.calcComparisonValue();
  }
  
  bool operator==(const IPV4Address& rhs) const {
    return this->calcComparisonValue() == rhs.calcComparisonValue();
  }

  private:
    long calcComparisonValue() const{
        return firstByte * 1'000'000'000 + secondByte * 1'000'000+ thirdByte * 1'000 + fourthByte; 
    }
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
