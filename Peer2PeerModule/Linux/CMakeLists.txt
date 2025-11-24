

add_subdirectory(MessageStore)
add_library(LinuxP2PNetworkImp
       LinuxP2PImp.cpp
       LinuxConnection.cpp
       SocketFunctionality.cpp
       ChunkSenderAndReceiver.cpp
)
target_link_libraries(LinuxP2PNetworkImp MessageStore)
target_link_libraries(LinuxP2PNetworkImp CommunicationPackModule)
