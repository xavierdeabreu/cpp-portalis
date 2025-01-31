#ifndef MOCK_MQTT_CLIENT_H
#define MOCK_MQTT_CLIENT_H

#include "MqttClient.h"
#include <gmock/gmock.h>

class MockMqttClient : public MqttClient {
    public:
        MockMqttClient(const std:: string& serverAddress, const std::string& clientId, const std::map<std::string, std::string>& certs)
            : MqttClient(serverAddress, clientId, certs) {}

        // mocking standard MQTT functions
        MOCK_METHOD(void, connect, (), (override));
        MOCK_METHOD(void, disconnect, (), (override));
        MOCK_METHOD(void, subscribe, (const std::string& topic, int qos), (override));
        MOCK_METHOD(void, publish, (const std::string& topic, const std::string& payload, int qos), (override));

        // mocking getters for SSL options and connection options
        MOCK_METHOD(const mqtt::ssl_options&, getSslOptions, (), (const, override));
        MOCK_METHOD(const mqtt::connect_options&, getConnectionOptions, (), (const, override));

};

#endif // MOCK_MQTT_CLIENT_H