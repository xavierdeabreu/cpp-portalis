cmake_minimum_required(VERSION 3.10)

# Define the project name
project(cpp-mqtt-client)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the necessary packages
find_package(PahoMqttCpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(open62541 REQUIRED)

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define source files
set(SOURCES
    src/main.cpp
    src/MqttClient.cpp
    src/AwsIoTConfig.cpp
    src/MesageProcessor.cpp
    src/OPCUAClient.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME}
    PahoMqttCpp::paho-mqttpp3
    ${PahoMqttC_LIB}
    spdlog::spdlog
    yaml-cpp
    jsoncpp
    open62541
)

# Enable testing
enable_testing()
add_subdirectory(tests)