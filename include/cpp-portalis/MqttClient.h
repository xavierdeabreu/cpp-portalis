#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <mqtt/client.h>
#include <spdlog/spdlog.h>
#include <string>

class MqttClient {
public:
    MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& certsDir);
    virtual ~MqttClient() = default; // virtual destructure for proper cleanup 

    virtual void connect();
    virtual void subscribe(const std::string& topic, int qos);
    virtual void publish(const std::string& topic, const std::string& payload, int qos);
    virtual void disconnect();

    // getters to access private members for unit testing
    virtual const mqtt::ssl_options& getSslOptions() const {return sslOptions;};
    virtual const mqtt::connect_options& getConnectionOptions() const { return connectionOptions; };

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