# Add test target
add_executable(UnitTests 
    MqttClientTest.cpp
    ../src/MqttClient.cpp
)

# Link test libraries
target_link_libraries(UnitTests
    gtest
    gtest_main
    PahoMqttCpp::paho-mqttpp3
    spdlog::spdlog
)

# Add tests to CTest
add_test(NAME UnitTests COMMAND UnitTests)

