# Add test target
add_executable(UnitTests 
    ${CMAKE_SOURCE_DIR}/tests/AwsIoTConfigTest.cpp
    ${CMAKE_SOURCE_DIR}/src/AwsIoTConfig.cpp
    ${CMAKE_SOURCE_DIR}/tests/MqttClientTest.cpp
    ${CMAKE_SOURCE_DIR}/src/MqttClient.cpp
)

# Link test libraries
target_link_libraries(UnitTests
    gmock
    gmock_main
    gtest
    gtest_main
    PahoMqttCpp::paho-mqttpp3
    spdlog::spdlog
    yaml-cpp
)

# Inlcude directories for test dependencies
target_include_directories(UnitTests PRIVATE
    ../include
)

# Add tests to CTest
add_test(NAME UnitTests COMMAND UnitTests)

