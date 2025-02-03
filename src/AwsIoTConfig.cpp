#include "AwsIoTConfig.h"
#include <stdexcept>

AwsIoTConfig::AwsIoTConfig(const std::string& configFile) {
    try {
        YAML::Node config = YAML::LoadFile(configFile);
        YAML::Node aws_iot = config["aws_iot"];

        // read aws settings
        endpoint = aws_iot["endpoint"].as<std::string>();
        client_id = aws_iot["client_id"].as<std::string>();

        // read topics and QoS Levels and store them in the topics map
        for (const auto& topic : aws_iot["topics"]) {
            topics[topic.first.as<std::string>()] = topic.second.as<int>();
        }

        // load certificates paths
        ca_cert = aws_iot["ca_cert"].as<std::string>();
        client_cert = aws_iot["client_cert"].as<std::string>();
        private_key = aws_iot["private_key"].as<std::string>();


    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading YAML config file: " + std::string(e.what()));
    }
}
