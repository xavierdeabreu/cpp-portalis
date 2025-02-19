#include "MessageProcessor.h"
#include <json/json.h>
#include <chrono>
#include <iostream>


MessageProcessor::MessageProcessor(MQTTClient& mqttClient, OPCUAClient& opcuaClient)
    : mqttClient(mqttClient), opcUaClient(opcUaClient) {}


// processes incoming messages from MQTT
void MessageProcessor::processIncomingMessage(const std::string& topic, const std::string& payload) {
    Json::CharReaderBuilder reader;
    Json::Value jsonMessage;
    std::string errors;
    std::istringstream(payload) >> payload;

    // parse the Json Payload into JsonMessage
    if (!Json::parseFromStream(reader, payload, &jsonMessage, &errors)) {
        std::cerr << "Failed to parse JSON: " << errors << std::endl;
        return;
    }

    // get the message type
    std::string messageType = jsonMessage["payload"]["messageType"].asString();

    // process the message based on its type
    if (messageType == "SCANNABLE_VALIDATION_RESPONSE") {
        handleScannableValidationResponse(jsonMessage);
    } else if (messageType == "DESTINATION_REPLY") {
        handleDestinationReply(jsonMessage);
    } else if (messageType == "PTL_UDPATE") {
        handlePTLUpdate(jsonMessage);
    } else {
        std::cerr << "Unknown message type: " << messageType << std::endl;
    }
}

// builds an outgoing JSON payload for MQTT
std::string MessageProcessor::buildOutgoingPayload(const std::string& messageType, const Json::Value& payload) {
    Json::Value outgoingMessage;

    // build the json payload
    outgoingMessage["payload"]["messageType"] = messageType;
    outgoingMessage["payload"]["requestId"] = payload["requestId"];
    outgoingMessage["payload"]["machineTimestamp"] = getCurrentTimestamp();

    // add optional fields if they exist
    if (payload.isMember("inductStationId")) {
        outgoingMessage["payload"]["inductStationId"] = payload["inductStationId"];
    }
    if (data.isMember("scanPointId")) {
        message["payload"]["scanPointId"] = data["scanPointId"].asString();
    }
    if (data.isMember("scannableIds")) {
        message["payload"]["scannableIds"] = data["scannableIds"];
    }
    if (data.isMember("dimensions") && !data["dimensions"].isNull()) {
        message["payload"]["dimensions"] = data["dimensions"];
    }
    if (data.isMember("actualDestinationId")) {
        message["payload"]["actualDestinationId"] = data["actualDestinationId"].asString();
    }
    if (data.isMember("divertStatus")) {
        message["payload"]["divertStatus"] = data["divertStatus"].asString();
    }

    // convert JSON string
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, outgoingMessage);
}

// sends an outgoing message via MQTT
void MessageProcessor::sendOutgoingMessage(const std::string& topic, const std::string&payload) {
    mqttClient.publish(topic, message);
}

// generates timestamp in ISO8601 format
std::string MessageProcessor::getCurrentTimestamp() {

    // get current timer
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;

    // format timestamp in ISO8601 with milliseconds
    oss << std::put_time(std::gmtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    oss << '.' << std::setw(3) << std::setfill('0') << (now_ms.count() % 1000);
    oss << "Z";

    return oss.str();
}