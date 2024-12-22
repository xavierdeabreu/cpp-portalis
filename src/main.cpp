#include "cpp-portalis/MqttClient.h"

const std::string SERVER_ADDRESS = "aws iot endpoint";
const std::string CLIENT_ID = "client id";
const std::string TOPIC = "topic";
const std::string CERTS_DIR = "certs directory";

int main() {
    try {
        // create mqtt client
        MqttClient mqttClient(SERVER_ADDRESS, CLIENT_ID, CERTS_DIR);

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