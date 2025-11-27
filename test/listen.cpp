#include "P2PNetwork.hpp"
#include "Linux/LinuxP2PNetworkImp.hpp"
#include <iostream>
#include <algorithm>

int main(){
  
  P2PNetwork netin{std::make_unique<LinuxP2PNetworkImp >(),"8081"};
  
  while(true){
     auto message = netin.getLatestMessage();
     if(message.has_value()){
       auto msgContent = message.value().content;
       //just to try out foreach of algorithm library
       auto print = [](const std::uint8_t & element) -> void{
            std::cout << element << "\n"; 
        };
       std::for_each(msgContent.begin(),msgContent.end(),print);
       break;
     }
  } 
  return 0;
};
