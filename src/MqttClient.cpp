#include "MqttClient.h"
#include <mqtt/message.h>


// create and initialise mqtt client
MqttClient::MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& caCert, const std::string& clientCert, const std::string& privateKey)
    : serverAddress(serverAddress), clientId(clientId), client(serverAddress, clientId) {
        setupSSL(caCert, clientCert, privateKey);
}

void MqttClient::setupSSL(const std::string& caCert, const std::string& clientCert, const std::string& privateKey) {

    // configure SSL Options
    sslOptions.set_trust_store(caCert);
    sslOptions.set_key_store(clientCert);
    sslOptions.set_private_key(privateKey);

    // set the SLL options in the connection options
    connectionOptions.set_ssl(sslOptions);
    connectionOptions.set_clean_session(true);

    spdlog::info("SSL setup completed with certificates loaded from config.");
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