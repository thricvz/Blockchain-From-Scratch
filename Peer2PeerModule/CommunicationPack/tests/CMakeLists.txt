enable_testing()
add_executable(CommunicationPackTest CommunicationPackTests.cpp)

target_link_libraries(
  CommunicationPackTest 
  GTest::gtest_main
  CommunicationPackModule 
)

add_test(NAME CommunicationPackTests COMMAND $<TARGET_FILE:CommunicationPackTest> )
