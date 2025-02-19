#ifndef OPC_UA_CLIENT_H
#define OPC_UA_CLIENT_H

#include <open62541/client.h>
#include <open62541/client_highlevel.h>
#include <string>
#include <json/json.h>

class OPCUAClient {
    public:
        OPCUAClient(const std::string endpoint);
        ~OPCUAClient();

        bool connect();
        void disconnect();
        bool readNode(const std::string& nodeId, Json::Value& outValue);
        bool writeNode(const std::string& nodeId, const Json::Value& value);
        bool callMethod(const std::string& nodeId, const Json::Value& arguments, Json::Value& outResponse);

    private:
        std::string endpoint;
        UA_Client* client;
};

#endif // OPC_UA_CLIENT_H

