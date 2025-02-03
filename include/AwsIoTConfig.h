#ifndef AWSIOTCONFIG_H
#define AWSIOTCONFIG_H

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

class AwsIoTConfig {
    private:
        std::string endpoint;
        std::string client_id;
        std::map<std::string, int> topics; // map of topics -> qos

        // certificate paths
        std::string ca_cert;
        std::string client_cert;
        std::string private_key;

    public:
        // Constructor to load from YAML
        AwsIoTConfig(const std::string& configFile);

        // Getters (no direct access to variables)
        std::string getEndpoint() const { return endpoint; }
        std::string getClientId() const { return client_id; }
        std::map<std::string, int> getTopics() const { return topics; }
        std::string getCaCert() const { return ca_cert; }
        std::string getClientCert() const { return client_cert; }
        std::string getPrivateKey() const { return private_key; }

};

#endif // AWSIOTCONFIG_H