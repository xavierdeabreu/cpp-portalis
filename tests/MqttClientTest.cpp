# include <gtest/gtest.h>
# include "MockMqttClient.h"

// Test mqtt client connection
TEST(MqttClientTest, TestConnection) {
    MockMqttClient mockClient("tcp://localhost:1883", "testClient", "./certs/");
    EXPECT_CALL(mockClient, connect()).Times(1);
    EXPECT_CALL(mockClient, disconnect()).Times(1);

    EXPECT_NO_THROW(mockClient.connect());
    EXPECT_NO_THROW(mockClient.disconnect());
}

// test for the subscribe method
TEST(MqttClientTest, TestSubscribed) {
    MockMqttClient mockClient("tcp://localhost:1883", "testClient", "./certs/");
    std::string topic = "testTopic";
    int qos = 1;

    EXPECT_CALL(mockClient, subscribe(topic, qos)).Times(1);

    EXPECT_NO_THROW(mockClient.subscribe(topic, qos));
}

// test for the publish method
TEST(MqttClientTest, TestPublish) {
    MockMqttClient mockClient("tcp:/localhost:1883", "testClient", "./certs/");
    std::string topic = "testTopic";
    std::string payload = "Hello, MQTT!";
    int qos = 1;

    EXPECT_CALL(mockClient, publish(topic, payload, qos)).Times(1);

    EXPECT_NO_THROW(mockClient.publish(topic, payload, qos));
}

// test SSL Configuration
TEST(MttClientTest, TestSSLSetup) {
    MockMqttClient mockClient("tcp://localhost:1883", "testClient", "./certs/");

    // create a valid ssl_options object
    mqtt::ssl_options sslOptions;

    EXPECT_CALL(mockClient, getSslOptions()).WillRepeatedly(testing::ReturnRef(sslOptions));

    EXPECT_NO_THROW(mockClient.getSslOptions());
}

// test Reconnection Logic
TEST(MqttClientTest, TestReconnection) {
    MockMqttClient mockClient("tcp://localhost:1883", "testClient", "./certs/");

    EXPECT_CALL(mockClient, disconnect()).Times(1);
    EXPECT_CALL(mockClient, connect()).Times(1);

    EXPECT_NO_THROW(mockClient.disconnect());
    EXPECT_NO_THROW(mockClient.connect());
}