#ifndef MOCK_MQTT_CLIENT_H
#define MOCK_MQTT_CLIENT_H

#include "cpp-portalis/MqttClient.h"
#include <gmock/gmock.h>

class MockMqttClient : public MqttClient {
    public:
        MockMqttClient(const std:: string& serverAddress, const std::string& clientId, const std::string& certsDir)
            : MqttClient(serverAddress, clientId, certsDir) {}

        MOCK_METHOD(void, connect, (), (override));
        MOCK_METHOD(void, disconnect, (), (override));
        MOCK_METHOD(void, subscribe, (const std::string& topic, int qos), (override));
        MOCK_METHOD(void, publish, (const std::string& topic, const std::string& payload, int qos), (override));
};

#endif // MOCK_MQTT_CLIENT_Hß