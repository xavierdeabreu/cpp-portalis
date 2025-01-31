#include "MqttClient.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <map>
#include <fstream>

// AWS IoT Configurations
const std::string SERVER_ADDRESS = "aws iot endpoint";
const std::string CLIENT_ID = "client id";
const std::string TOPIC = "topic";

// Funtion to load configurations from YAML file
std::map<std::string, std::string> loadConfig(const std::string& configFile) {
    try {
        YAML::Node config = YAML::LoadFile(configFile);

        return {
            {"ca_cert", config["ca_cert"].as<std::string>()},
            {"client_cert", config["client_cert"].as<std::string>()},
            {"private_key", config["private_key"].as<std::string>()}
        };
    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading YAML config file: " + std::string(e.what()));
    }
}

int main() {
    try {

        // get config file path from environment variable 
        std::string configPath = std::getenv("CONFIG_FILE_PATH") ? std::getenv("CONFIG_FILE_PATH") : "config/certs.yaml";

        // load MQTT certificate paths from YAML file
        std::map<std::string, std::string> certs = loadConfig(configPath);

        // create mqtt client
        MqttClient mqttClient(SERVER_ADDRESS, CLIENT_ID, certs);

        // connect to the mqtt broker
        mqttClient.connect();

        // subscribe to topic
        mqttClient.subscribe(TOPIC, 1);

        // publish a test message
        mqttClient.publish(TOPIC, "Hello from cpp-portalis!", 1);

        // wait for 1- seconds to process incoming messages
        std::this_thread::sleep_for(std::chrono::seconds(10));

        // disconnect from the broker 
        mqttClient.disconnect();
    } catch (const mqtt::exception& exc) { // handles mqtt-specific exceptions
        spdlog::error("MQTT Error: {}", exc.what());
        return 1;
    } catch (const std::exception& e) { // handles other standard exceptions
        spdlog::error("General Error: {}", e.what());
        return 1;
    }
    return 0;
}