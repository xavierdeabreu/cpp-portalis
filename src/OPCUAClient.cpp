#include "OPCUAClient.h"
#include <iostream>

OPCUAClient::OPCUAClient(const std::string endpoint): endpoint(endpoint), client(nullptr) {}


//  destructor to ensure any allocated resources are freed after disconnection
OPCUACLient::~OPCUAClient() {
    if (client) {
        UA_Client_disconnect(client);
        UA_Client_delete(client);
    }
}

// establish a connection to the OPC UA Server
bool OPDUAClient::connect() {
    client = UA_Client_new(); // allocate a new client instance

    // handle errors creating OPC UA Client instance
    if (!client) {
        std::cerr << "Failed to create OPC UA client." << std::endl;
        return false;
    }

    // configure newly created OPC UA Client
    UA_Client_setDefault(UA_Client_getConfig(client)); // set the default config
    
    // connect to the OPC UA Server
    UA_StatusCode status = UA_Client_connect(client, endpoint.c_str());

    // check if the connection was successful or not
    if (status != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to connect to OPC UA Server: " << UA_StatusCode_name(status) << std::endl;
        UA_Client_delete(client);
        client = nullptr;
        return false;
    }
    return true;
}

// disconnect from the OPC UA Server and clean up
void OPCUAClient::disconnect() {
    if (client) {
        UA_Client_disconnect(client);
        UA_Client_delete(client);
        client = nullptr;
    }
}

// reads a node value form the OPC UA Server and stores it in a JSON Object
bool OPCUAClient::readNode(const std::string& nodeID, Json::Vale& outValue) {
    
    // check wheter the client is connected or not 
    if (!client) {
        std::cerr << "OPC UA Client is not connected." << std::endl;
        return false;
    }

    // declare and initialize a UA_Variant structure to hold the read value
    UA_Variant value;
    UA_Variant_init(&value);

    // convert nodeID string to UA_NodeId structure
    UA_NodeId uaNodeId = UA_NODEID_STRING_ALLOC(1, modeId.c_str());

    // perform the read operation
    UA_StatusCode status = UA_Client_readValueAttribute(client, uaNodeId, &value);

    // clear the allocated UA_NodeId to prevent memory leaks 
    UA_NodeId_clear(&uaNodeId);

    // check if the read operation was successful
    if(status != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to read OPC UA node: " << nodeId << " - " << UA_StatusCode_name(status) << std::endl;
        return false;
    }

    // ensure the read value is scalar and of a supported type
    if (UA_Variant_isScalar(&value) && value.type == &UA_TYPES[UA_TYPES_DOUBLE]) {
        outValue = value.data ? *static_cast<double*>(value.data) : 0.0;
    } else {
        std::cerr << "Unsupported daa type for node: " << nodeId << std::endl;
        return false;
    }

    // clear the UA_Variant to free from allocated memory
    UA_Variant_clear(&value);
    return true;
}

// writes a JSON-provided value to an OPC UA node
