#include <gtest/gtest.h>
#include "AwsIoTConfig.h"
#include <fstream>

// Mock YAML configuration for testing
const std::string validConfig = R"(
aws_iot:
  endpoint: "test-endpoint"
  client_id: "test-client-id"
  topics:
    "test/topic1": 1
    "test/topic2": 0
  ca_cert: "./test_certs/ca.pem"
  client_cert: "./test_certs/cert.pem"
  private_key: "./test_certs/key.pem"
)";

const std::string missingFieldsConfig = R"(
aws_iot:
  endpoint: "test-endpoint"
)"; // Missing client_id, topics, and certs

const std::string invalidConfig = R"(
aws_iot:
  endpoint: 12345
  client_id: true
)"; // Invalid data types

// helper function to write a test YAML File
void writeTestConfig(const std::string& fileName, const std::string& content) {
    std::ofstream outFile(fileName);
    outFile << content;
    outFile.close();
}


// test for loading a valid configuration
TEST(AwsIoTConfigTest, LoadValidConfig) {
    std::string testFile = "valid_config.yaml";
    writeTestConfig(testFile, validConfig); // write YAML file

    AwsIoTConfig awsIoTConfig(testFile); // load configuration

    // Verify AWS settings
    EXPECT_EQ(awsIoTConfig.getEndpoint(), "test-endpoint");
    EXPECT_EQ(awsIoTConfig.getClientId(), "test-client-id");

    // Verify topics & QoS levels
    EXPECT_EQ(awsIoTConfig.getTopics().size(), 2);
    EXPECT_EQ(awsIoTConfig.getTopics().at("test/topic1"), 1);
    EXPECT_EQ(awsIoTConfig.getTopics().at("test/topic2"), 0);

    // Verify certificate paths
    EXPECT_EQ(awsIoTConfig.getCaCert(), "./test_certs/ca.pem");
    EXPECT_EQ(awsIoTConfig.getClientCert(), "./test_certs/cert.pem");
    EXPECT_EQ(awsIoTConfig.getPrivateKey(), "./test_certs/key.pem");
}

// test for handling missing fields in the YAML file
TEST(AwsIoTConfigTest, HandleMissingFields) {
    std::string testFile = "test_missing_fields.yaml";
    writeTestConfig(testFile, missingFieldsConfig);

    EXPECT_THROW(AwsIoTConfig config(testFile), std::runtime_error);
}

// test for handling an invalid YAML configuration
TEST(AwsIoTConfigTest, HandleInvalidConfig) {
    std::string testFile = "test_invalid_config.yaml";
    writeTestConfig(testFile, invalidConfig);

    EXPECT_THROW(AwsIoTConfig config(testFile), std::runtime_error);
}

// test for missing YAML file
TEST(AwsIoTConfigTest, HandleMissingFile) {
    std::string nonExistentFile = "non_existent_config.yaml";

    EXPECT_THROW(AwsIoTConfig config(nonExistentFile), std::runtime_error);
}

