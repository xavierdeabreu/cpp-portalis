# include <gtest/gtest.h>
# include "MockMqttClient.h"

// Example test case using the mock
TEST(MqttClientTest, TestConnection) {
    MockMqttClient mockClient("tcp://localhost:1883", "testClient", "./certs/");
    EXPECT_CALL(mockClient, connect()).Times(1);
    EXPECT_CALL(mockClient, disconnect()).Times(1);

    EXPECT_NO_THROW(mockClient.connect());
    EXPECT_NO_THROW(mockClient.disconnect());
}