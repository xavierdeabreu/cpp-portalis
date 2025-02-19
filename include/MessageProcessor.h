#ifndef MESSAGE_PROCESSOR_H
#define MESSAGE_PROCESSOR_H

#include <string>
#include <json/json.h>
#include "MQTTClient.h"
#include "OPCUAClient.h"


class MessageProcessor {
    public:
        MessageProcessor(MQTTClient& mqttCient, OPCUAClient& opcuaClient);
        void processIncomingMessage(const std::string& topic, const std::string& payload);
        void sendOutgoingMessage(const std::string& topic, const std::string& payload);

    private:
        MQTTClient& mqttClient;
        OPCUAClient& opcuaClient;

        void handleScannableIdValidationResponse(const Json::Value& payload);
        void handleDestinationReply(const Json::Value& payload);
        void handlePTLUpdate(const Json::Value& payload);
        std::string buildOutgoingPayload(const std::string& messageType, const Json::Value& payload);
};

#endif // MESSAGE_PROCESSOR_H