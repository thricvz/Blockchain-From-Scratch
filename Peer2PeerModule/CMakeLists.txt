

include_directories(include/)
include_directories(include/Linux/MessageStore)
include_directories(include/Linux)
include_directories(include/CommunicationPack/)

add_subdirectory(CommunicationPack)
add_subdirectory(Linux)

add_library(P2PNetworkLib P2PNetwork.cpp )
