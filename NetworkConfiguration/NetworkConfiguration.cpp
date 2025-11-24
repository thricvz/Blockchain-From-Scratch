#include "NetworkConfiguration.hpp" 
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <exception>


NetworkConfiguration::NetworkConfiguration(const std::string& configurationFile){
  try{
    std::FILE* configFile = std::fopen(configurationFile.c_str(), "r");
    configJSON = json::parse(configFile);
    std::fclose(configFile);
  }catch(std::exception &error){
    std::cerr << error.what() << std::endl;
  }

};

std::string NetworkConfiguration::getListeningPort() const{
    return configJSON["host_port"];

}; 
std::vector<IPV4Address> NetworkConfiguration::getConnectionEstablishers() const{
    auto availableNodes = configJSON["connection_nodes"];
    std::vector<IPV4Address> availableNodesIp{};
    for(auto node : availableNodes){
        availableNodesIp.push_back(charToAddress(node.get<std::string>().c_str()));

    }
    return availableNodesIp;
}; 
