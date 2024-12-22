#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <mqtt/client.h>
#include <spdlog/spdlog.h>
#include <string>

class MqttClient {
public:
    MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& certsDir);

    void connect();
    void subscribe(const std::string& topic, int qos);
    void publish(const std::string& topic, const std::string& payload, int qos);
    void disconnect();

private:
    std::string serverAddress;
    std::string clientId;
    std::string certsDir;
    mqtt::client client;
    mqtt::ssl_options sslOptions;
    mqtt::connect_options connectionOptions;

    void setupSSL();
};

#endif // MQTTCLIENT_H