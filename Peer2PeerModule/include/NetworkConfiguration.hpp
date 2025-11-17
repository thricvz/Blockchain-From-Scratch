#pragma once
#include "IPV4Address.hpp"
#include <string>
#include <vector>

class NetworkConfiguration{
  public:
    NetworkConfiguration(const std::string& configurationFile);
    std::string getListeningPort() const; 
    std::vector<IPV4Address> getConnectionEstablishers() const; 
     
};
