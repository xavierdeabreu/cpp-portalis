#include "AwsIoTConfig.h"
#include "MqttClient.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <map>
#include <fstream>

int main() {
    try {
        // get config file path from environment variable 
        std::string configPath = std::getenv("CONFIG_FILE_PATH") ? std::getenv("CONFIG_FILE_PATH") : "config/certs.yaml";

        // load aws iot configuration
        AwsIoTConfig awsIoTConfig(configPath);

        // create mqtt client
        MqttClient mqttClient(awsIoTConfig.getEndpoint(), awsIoTConfig.getClientId(), awsIoTConfig.getCaCert(), awsIoTConfig.getClientCert(), awsIoTConfig.getPrivateKey());

        // connect to the mqtt broker
        mqttClient.connect();

        // subscribe to topics dynamicaly
        for (const auto& topic : awsIoTConfig.getTopics()) {
            spdlog::info("Subscribing to topic: {} with QoS: {}", topic.first, topic.second);
            mqttClient.subscribe(topic.first, topic.second);
        }

        // publish a test message for each topic
        for (const auto& topic : awsIoTConfig.getTopics()) {
            mqttClient.publish(topic.first, "Hello from cpp-portalis!", topic.second);
        }

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