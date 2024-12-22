#include "cpp-portalis/MqttClient.h"
#include <mqtt/message.h>


// create and initialise mqtt client
MqttClient::MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& certsDir)
    : serverAddress(serverAddress), clientId(clientId), certsDir(certsDir), client(serverAddress, clientId) {
        setupSSL();
}

void MqttClient::setupSSL() {
    // configure SSL Options
    sslOptions.set_trust_store(certsDir + "AmazonRootCA1.pem");
    sslOptions.set_key_store(certsDir + "device.pem.crt");
    sslOptions.set_private_key(certsDir + "private.pem.key");

    // set the SLL options in the connection options
    connectionOptions.set_ssl(sslOptions);
    connectionOptions.set_clean_session(true);

    spdlog::info("SSL setup completed.");
}

void MqttClient::connect() {
    spdlog::info("Connecting to MQTT Broker at {}...", serverAddress);
    client.connect(connectionOptions);
    spdlog::info("Connected to MQTT Broker.");
}

void MqttClient::subscribe(const std::string& topic, int qos) {
    spdlog::info("Subscribing to topic {}...", topic);
    client.subscribe(topic, qos);
}

void MqttClient::publish(const std::string& topic, const std::string& payload, int qos) {
    spdlog::info("Publishing message to topic {}...", topic);
    // build message
    auto message = mqtt::make_message(topic, payload);
    // set qos for message
    message->set_qos(qos);
    // pubish message
    client.publish(message);
}

void MqttClient::disconnect() {
    spdlog::info("Disconnecting from MQTT Broker...");
    client.disconnect();
    spdlog::info("Disconnected from MQTT Broker.");
}