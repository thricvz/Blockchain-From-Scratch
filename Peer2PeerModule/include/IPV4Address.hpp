#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>

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


static IPV4Address charToAddress(const char * input){
    
    auto calculateByteWorth = [](char *& byteSegment)->std::uint8_t{
        auto getDigitValue = [](char character) -> std::uint8_t{
            return  character -'0';
        };
       
        std::uint8_t byteValue{};
        std::vector<uint8_t> digits{};

        while((*byteSegment)){
            if(!std::strncmp(byteSegment,".",1)){
              byteSegment++;
              break;
            }

            digits.push_back(getDigitValue(*byteSegment)); 
            byteSegment++;
        }
        

        auto numberDigits = digits.size();  
        for(int index = 0;index < numberDigits ;index++){
           byteValue += digits[index] * pow(10,numberDigits-(index+1));
        }

        return byteValue;
    };

   char * stream = new char[strlen(input)] ;
   char* const streamStart = stream; 
   strcpy(stream, input);

   auto result = IPV4Address{
      calculateByteWorth(stream),
      calculateByteWorth(stream),
      calculateByteWorth(stream),
      calculateByteWorth(stream)
   };  

  delete[] streamStart;
  return result;
};


