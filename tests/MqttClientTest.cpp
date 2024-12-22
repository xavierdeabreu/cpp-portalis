# include <gtest/gtest.h>
# include "cpp-portalis/MqttClient.h"

// Example test case
TEST(MqttClientTest, TestConnection) {
    MqttClient client("tcp//localhost:1883", "testClient", "./certs/");
    EXPECT_NO_THROW(client.connect());
    client.disconnect();
}

TEST(MqttClientTest, TestPublish) {
    MqttClient client("tcp//localhost:1883", "testClient", "./certs/");
    client.connect();
    EXPECT_NO_THROW(client.publish("test/topic", "Hello, MQTT!", 1));
    client.disconnect();
}