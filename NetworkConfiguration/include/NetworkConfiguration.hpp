#pragma once
#include "IPV4Address.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

class NetworkConfiguration{
  public:
    NetworkConfiguration(const std::string& configurationFile);
    std::string getListeningPort() const; 
    std::vector<IPV4Address> getConnectionEstablishers() const; 
  
  private:
    json configJSON{}; 
};
