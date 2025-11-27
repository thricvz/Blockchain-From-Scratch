

add_executable(listen listen.cpp)
add_executable(connect connect.cpp)

target_link_libraries(listen LinuxP2PNetworkImp P2PNetworkLib)
target_link_libraries(connect LinuxP2PNetworkImp P2PNetworkLib)
