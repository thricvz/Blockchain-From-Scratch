

include_directories(include)


add_library(LinuxP2PImplementation LinuxP2PImp.cpp)
add_executable(main main.cpp)
target_link_libraries(main LinuxP2PImplementation)
