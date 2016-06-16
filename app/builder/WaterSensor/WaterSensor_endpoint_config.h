// This file is generated by Ember Desktop.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __AF_ENDPOINT_CONFIG__
#define __AF_ENDPOINT_CONFIG__


// Fixed number of defined endpoints
#define FIXED_ENDPOINT_COUNT (1)


// Generated defaults
#if BIGENDIAN_CPU
#define GENERATED_DEFAULTS { \
6,'W','u','l','i','a','n',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 /* 0,Default value: Basic,manufacturer name */, \
6,'T','-','S','J','0','1',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 /* 33,Default value: Basic,model identifier */, \
8,'2','0','1','6','0','4','0','5',0,0,0,0,0,0,0,0 /* 66,Default value: Basic,date code */, \
  }
#else // ! BIGENDIAN_CPU
#define GENERATED_DEFAULTS { \
6,'W','u','l','i','a','n',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 /* 0,Default value: Basic,manufacturer name */, \
6,'T','-','S','J','0','1',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 /* 33,Default value: Basic,model identifier */, \
8,'2','0','1','6','0','4','0','5',0,0,0,0,0,0,0,0 /* 66,Default value: Basic,date code */, \
  }
#endif // BIGENDIAN_CPU




// Generated attributes
#define GENERATED_ATTRIBUTES { \
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x02 } }, /* 0 / Basic / ZCL version*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x02 } }, /* 1 / Basic / application version*/\
    { 0x0002, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x01 } }, /* 2 / Basic / stack version*/\
    { 0x0003, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x01 } }, /* 3 / Basic / hardware version*/\
    { 0x0004, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)&(generatedDefaults[0]) } }, /* 4 / Basic / manufacturer name*/\
    { 0x0005, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)&(generatedDefaults[33]) } }, /* 5 / Basic / model identifier*/\
    { 0x0006, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)&(generatedDefaults[66]) } }, /* 6 / Basic / date code*/\
    { 0x0007, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x03 } }, /* 7 / Basic / power source*/\
    { 0x0010, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 8 / Basic / location description*/\
    { 0x0011, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 9 / Basic / physical environment*/\
    { 0x0012, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x01 } }, /* 10 / Basic / device enabled*/\
    { 0x0020, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00UL } }, /* 11 / Power Configuration / battery voltage*/\
    { 0x0035, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x01 } }, /* 12 / Power Configuration / battery alarm mask*/\
    { 0x0036, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x1A } }, /* 13 / Power Configuration / battery voltage min threshold*/\
    { 0x0000, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 14 / Identify / identify time*/\
    { 0x0000, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, /* 15 / IAS Zone / zone state*/\
    { 0x0001, ZCL_ENUM16_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x002a } }, /* 16 / IAS Zone / zone type*/\
    { 0x0002, ZCL_BITMAP16_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0000 } }, /* 17 / IAS Zone / zone status*/\
    { 0x0010, ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE, 8, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE), { NULL } }, /* 18 / IAS Zone / IAS CIE address*/\
    { 0x0011, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0xff } }, /* 19 / IAS Zone / Zone ID*/\
    { 0x0000, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 20 / Diagnostics / number of resets*/\
    { 0x0104, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 21 / Diagnostics / mac tx unicast retry*/\
    { 0x010A, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 22 / Diagnostics / aps tx unicast retries*/\
    { 0x010C, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 23 / Diagnostics / route discovery initiated*/\
    { 0x010D, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 24 / Diagnostics / neighbor added*/\
    { 0x010E, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 25 / Diagnostics / neighbor moved*/\
    { 0x010F, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 26 / Diagnostics / neighbor stale*/\
    { 0x0110, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 27 / Diagnostics / join indication*/\
    { 0x0111, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 28 / Diagnostics / child moved*/\
    { 0x011B, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 29 / Diagnostics / average mac retry per aps message sent*/\
    { 0x011C, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 30 / Diagnostics / last message lqi*/\
    { 0x011D, ZCL_INT8S_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000 } }, /* 31 / Diagnostics / last message rssi*/\
  }


// Cluster function static arrays
#define GENERATED_FUNCTION_ARRAYS \
PGM EmberAfGenericClusterFunction emberAfFuncArrayPowerConfigClusterServer[] = { (EmberAfGenericClusterFunction)emberAfPowerConfigClusterServerAttributeChangedCallback}; \
PGM EmberAfGenericClusterFunction emberAfFuncArrayIdentifyClusterServer[] = { (EmberAfGenericClusterFunction)emberAfIdentifyClusterServerInitCallback,(EmberAfGenericClusterFunction)emberAfIdentifyClusterServerAttributeChangedCallback}; \
PGM EmberAfGenericClusterFunction emberAfFuncArrayIasZoneClusterServer[] = { (EmberAfGenericClusterFunction)emberAfIasZoneClusterServerInitCallback,(EmberAfGenericClusterFunction)emberAfIasZoneClusterServerPreAttributeChangedCallback}; \


// Clusters defitions
#define GENERATED_CLUSTERS { \
    { 0x0000, (EmberAfAttributeMetadata*)&(generatedAttributes[0]), 11, 0, (CLUSTER_MASK_SERVER), NULL,  },    \
    { 0x0001, (EmberAfAttributeMetadata*)&(generatedAttributes[11]), 3, 0, (CLUSTER_MASK_SERVER| CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION), emberAfFuncArrayPowerConfigClusterServer, },    \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[14]), 1, 2, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION| CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION), emberAfFuncArrayIdentifyClusterServer, },    \
    { 0x0500, (EmberAfAttributeMetadata*)&(generatedAttributes[15]), 5, 14, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION| CLUSTER_MASK_PRE_ATTRIBUTE_CHANGED_FUNCTION), emberAfFuncArrayIasZoneClusterServer, },    \
    { 0x0B05, (EmberAfAttributeMetadata*)&(generatedAttributes[20]), 12, 0, (CLUSTER_MASK_SERVER), NULL,  },    \
  }


// Endpoint types
#define GENERATED_ENDPOINT_TYPES {        \
    { (EmberAfCluster*)&(generatedClusters[0]), 5, 16 }, \
  }


// Networks
#define EM_AF_GENERATED_NETWORK_TYPES { \
  EM_AF_NETWORK_TYPE_ZIGBEE_PRO, /* Primary */ \
}
#define EM_AF_GENERATED_ZIGBEE_PRO_NETWORKS { \
  { \
    /* Primary */ \
    ZA_SLEEPY_END_DEVICE, \
    EMBER_AF_SECURITY_PROFILE_HA, \
  }, \
}
#define EM_AF_GENERATED_NETWORK_STRINGS  \
  "Primary (pro)", \


// Cluster manufacturer codes
#define GENERATED_CLUSTER_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT (0)

// Attribute manufacturer codes
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT (0)


// Largest attribute size is needed for various buffers
#define ATTRIBUTE_LARGEST (33)
// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (132)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE 16

// Array of endpoints that are supported
#define FIXED_ENDPOINT_ARRAY { 1 }

// Array of profile ids
#define FIXED_PROFILE_IDS { 260 }

// Array of profile ids
#define FIXED_DEVICE_IDS { 1026 }

// Array of profile ids
#define FIXED_DEVICE_VERSIONS { 0 }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES { 0 }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS { 0 }


// Code used to configure the cluster event mechanism
#define EMBER_AF_GENERATED_EVENT_CODE \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl1; \
  EmberEventControl emberAfIasZoneClusterServerTickCallbackControl1; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0PressedEventControl; \
  extern void emberAfPluginButtonInterfaceButton0PressedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0ReleasedEventControl; \
  extern void emberAfPluginButtonInterfaceButton0ReleasedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1PressedEventControl; \
  extern void emberAfPluginButtonInterfaceButton1PressedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1ReleasedEventControl; \
  extern void emberAfPluginButtonInterfaceButton1ReleasedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButton2PressedEventControl; \
  extern void emberAfPluginButtonInterfaceButton2PressedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButton2ReleasedEventControl; \
  extern void emberAfPluginButtonInterfaceButton2ReleasedEventHandler(void); \
  extern EmberEventControl emberAfPluginButtonInterfaceButtonTimeoutEventControl; \
  extern void emberAfPluginButtonInterfaceButtonTimeoutEventHandler(void); \
  extern EmberEventControl emberAfPluginConnectionManagerRebootEventControl; \
  extern void emberAfPluginConnectionManagerRebootEventHandler(void); \
  extern EmberEventControl emberAfPluginConnectionManagerRejoinEventControl; \
  extern void emberAfPluginConnectionManagerRejoinEventHandler(void); \
  extern EmberEventControl emberAfPluginConnectionManagerPollEventControl; \
  extern void emberAfPluginConnectionManagerPollEventHandler(void); \
  extern EmberEventControl emberAfPluginEzmodeCommissioningStateEventControl; \
  extern void emberAfPluginEzmodeCommissioningStateEventHandler(void); \
  extern EmberEventControl emberAfPluginFormAndJoinCleanupEventControl; \
  extern void emberAfPluginFormAndJoinCleanupEventHandler(void); \
  extern EmberEventControl emberAfPluginGpioSensorDebounceEventControl; \
  extern void emberAfPluginGpioSensorDebounceEventHandler(void); \
  extern EmberEventControl emberAfPluginGpioSensorInterruptEventControl; \
  extern void emberAfPluginGpioSensorInterruptEventHandler(void); \
  extern EmberEventControl emberAfPluginIasZoneServerInitEventControl; \
  extern void emberAfPluginIasZoneServerInitEventHandler(void); \
  extern EmberEventControl emberAfPluginLedBlinkLedEventFunctionEventControl; \
  extern void emberAfPluginLedBlinkLedEventFunctionEventHandler(void); \
  extern EmberEventControl emberAfPluginLowVoltageShutdownCheckForShutdownEventControl; \
  extern void emberAfPluginLowVoltageShutdownCheckForShutdownEventHandler(void); \
  extern EmberEventControl emberAfPluginNetworkFindTickEventControl; \
  extern void emberAfPluginNetworkFindTickEventHandler(void); \
  extern EmberEventControl emberAfPluginReportingTickEventControl; \
  extern void emberAfPluginReportingTickEventHandler(void); \
  extern EmberEventControl emberAfPluginSecuritySensorInitEventControl; \
  extern void emberAfPluginSecuritySensorInitEventHandler(void); \
  extern EmberEventControl emberAfPluginSecuritySensorInitialReportEventControl; \
  extern void emberAfPluginSecuritySensorInitialReportEventHandler(void); \
  extern EmberEventControl emberAfPluginSecuritySensorButtonPressCountEventControl; \
  extern void emberAfPluginSecuritySensorButtonPressCountEventHandler(void); \
  static void networkEventWrapper(EmberEventControl *control, EmberAfNetworkEventHandler handler, uint8_t networkIndex) \
  { \
    emberAfPushNetworkIndex(networkIndex); \
    emberEventControlSetInactive(*control); \
    (*handler)(); \
    emberAfPopNetworkIndex(); \
  } \
  EmberEventControl emberAfPluginEndDeviceSupportPollingNetworkEventControls[1]; \
  extern void emberAfPluginEndDeviceSupportPollingNetworkEventHandler(void); \
  void emberAfPluginEndDeviceSupportPollingNetworkEventWrapper0(void) { networkEventWrapper(&emberAfPluginEndDeviceSupportPollingNetworkEventControls[0], emberAfPluginEndDeviceSupportPollingNetworkEventHandler, 0); } \
  EmberEventControl emberAfPluginEndDeviceSupportMoveNetworkEventControls[1]; \
  extern void emberAfPluginEndDeviceSupportMoveNetworkEventHandler(void); \
  void emberAfPluginEndDeviceSupportMoveNetworkEventWrapper0(void) { networkEventWrapper(&emberAfPluginEndDeviceSupportMoveNetworkEventControls[0], emberAfPluginEndDeviceSupportMoveNetworkEventHandler, 0); } \
  extern EmberEventControl emberAfPluginSecuritySensorStateSupervisionReportsControl; \
  extern void emberAfPluginSecuritySensorStateSupervisionReportsHandler(void); \
  static void clusterTickWrapper(EmberEventControl *control, EmberAfTickFunction callback, uint8_t endpoint) \
  { \
    emberAfPushEndpointNetworkIndex(endpoint); \
    emberEventControlSetInactive(*control); \
    (*callback)(endpoint); \
    emberAfPopNetworkIndex(); \
  } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction1(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallback, 1); } \
  void emberAfIasZoneClusterServerTickCallbackWrapperFunction1(void) { clusterTickWrapper(&emberAfIasZoneClusterServerTickCallbackControl1, emberAfIasZoneClusterServerTickCallback, 1); } \


// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS   \
  { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfIasZoneClusterServerTickCallbackControl1, emberAfIasZoneClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfPluginButtonInterfaceButton0PressedEventControl, emberAfPluginButtonInterfaceButton0PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton0ReleasedEventControl, emberAfPluginButtonInterfaceButton0ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1PressedEventControl, emberAfPluginButtonInterfaceButton1PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1ReleasedEventControl, emberAfPluginButtonInterfaceButton1ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton2PressedEventControl, emberAfPluginButtonInterfaceButton2PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton2ReleasedEventControl, emberAfPluginButtonInterfaceButton2ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButtonTimeoutEventControl, emberAfPluginButtonInterfaceButtonTimeoutEventHandler }, \
  { &emberAfPluginConnectionManagerRebootEventControl, emberAfPluginConnectionManagerRebootEventHandler }, \
  { &emberAfPluginConnectionManagerRejoinEventControl, emberAfPluginConnectionManagerRejoinEventHandler }, \
  { &emberAfPluginConnectionManagerPollEventControl, emberAfPluginConnectionManagerPollEventHandler }, \
  { &emberAfPluginEzmodeCommissioningStateEventControl, emberAfPluginEzmodeCommissioningStateEventHandler }, \
  { &emberAfPluginFormAndJoinCleanupEventControl, emberAfPluginFormAndJoinCleanupEventHandler }, \
  { &emberAfPluginGpioSensorDebounceEventControl, emberAfPluginGpioSensorDebounceEventHandler }, \
  { &emberAfPluginGpioSensorInterruptEventControl, emberAfPluginGpioSensorInterruptEventHandler }, \
  { &emberAfPluginIasZoneServerInitEventControl, emberAfPluginIasZoneServerInitEventHandler }, \
  { &emberAfPluginLedBlinkLedEventFunctionEventControl, emberAfPluginLedBlinkLedEventFunctionEventHandler }, \
  { &emberAfPluginLowVoltageShutdownCheckForShutdownEventControl, emberAfPluginLowVoltageShutdownCheckForShutdownEventHandler }, \
  { &emberAfPluginNetworkFindTickEventControl, emberAfPluginNetworkFindTickEventHandler }, \
  { &emberAfPluginReportingTickEventControl, emberAfPluginReportingTickEventHandler }, \
  { &emberAfPluginSecuritySensorInitEventControl, emberAfPluginSecuritySensorInitEventHandler }, \
  { &emberAfPluginSecuritySensorInitialReportEventControl, emberAfPluginSecuritySensorInitialReportEventHandler }, \
  { &emberAfPluginSecuritySensorButtonPressCountEventControl, emberAfPluginSecuritySensorButtonPressCountEventHandler }, \
  { &emberAfPluginEndDeviceSupportPollingNetworkEventControls[0], emberAfPluginEndDeviceSupportPollingNetworkEventWrapper0 }, \
  { &emberAfPluginEndDeviceSupportMoveNetworkEventControls[0], emberAfPluginEndDeviceSupportMoveNetworkEventWrapper0 }, \
  { &emberAfPluginSecuritySensorStateSupervisionReportsControl, emberAfPluginSecuritySensorStateSupervisionReportsHandler }, \


#define EMBER_AF_GENERATED_EVENT_STRINGS   \
  "Identify Cluster Server EP 1",  \
  "IAS Zone Cluster Server EP 1",  \
  "Button Interface Plugin Button0Pressed",  \
  "Button Interface Plugin Button0Released",  \
  "Button Interface Plugin Button1Pressed",  \
  "Button Interface Plugin Button1Released",  \
  "Button Interface Plugin Button2Pressed",  \
  "Button Interface Plugin Button2Released",  \
  "Button Interface Plugin ButtonTimeout",  \
  "Connection Manager Plugin Reboot",  \
  "Connection Manager Plugin Rejoin",  \
  "Connection Manager Plugin Poll",  \
  "EZ-Mode Commissioning Plugin State",  \
  "Form and Join Library Plugin Cleanup",  \
  "GPIO Sensor Interface Plugin Debounce",  \
  "GPIO Sensor Interface Plugin Interrupt",  \
  "IAS Zone Server Plugin Init",  \
  "LED Blinking Plugin LedEventFunction",  \
  "Low Voltage Shutdown Plugin CheckForShutdown",  \
  "Network Find Plugin Tick",  \
  "Reporting Plugin Tick",  \
  "Security Sensor Interface Plugin Init",  \
  "Security Sensor Interface Plugin InitialReport",  \
  "Security Sensor Interface Plugin ButtonPressCount",  \
  "End Device Support Plugin Polling NWK 0", \
  "End Device Support Plugin Move NWK 0", \
  "emberAfPluginSecuritySensorStateSupervisionReportsControl Custom",  \


// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 2

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1}, \
{ 0x1, 0x500, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIasZoneClusterServerTickCallbackControl1}


#define EMBER_AF_GENERATED_PLUGIN_INIT_FUNCTION_DECLARATIONS \
  void emberAfPluginConnectionManagerInitCallback(void); \
  void emberAfPluginEndDeviceSupportInitCallback(void); \
  void emberAfPluginGpioSensorInitCallback(void); \
  void emberAfPluginLowVoltageShutdownInitCallback(void); \
  void emberAfPluginNetworkFindInitCallback(void); \
  void emberAfPluginReportingInitCallback(void); \
  void emberAfPluginSecuritySensorInitCallback(void); \
  void emberAfPluginTamperSwitchInitCallback(void); \
  void emberAfPluginCountersInitCallback(void); \


#define EMBER_AF_GENERATED_PLUGIN_INIT_FUNCTION_CALLS \
  emberAfPluginConnectionManagerInitCallback(); \
  emberAfPluginEndDeviceSupportInitCallback(); \
  emberAfPluginGpioSensorInitCallback(); \
  emberAfPluginLowVoltageShutdownInitCallback(); \
  emberAfPluginNetworkFindInitCallback(); \
  emberAfPluginReportingInitCallback(); \
  emberAfPluginSecuritySensorInitCallback(); \
  emberAfPluginTamperSwitchInitCallback(); \
  emberAfPluginCountersInitCallback(); \


#define EMBER_AF_GENERATED_PLUGIN_NCP_INIT_FUNCTION_DECLARATIONS \
  void emberAfPluginAddressTableNcpInitCallback(bool memoryAllocation); \


#define EMBER_AF_GENERATED_PLUGIN_NCP_INIT_FUNCTION_CALLS \
  emberAfPluginAddressTableNcpInitCallback(memoryAllocation); \


#define EMBER_AF_GENERATED_PLUGIN_STACK_STATUS_FUNCTION_DECLARATIONS \
  void emberAfPluginConnectionManagerStackStatusCallback(EmberStatus status); \
  void emberAfPluginEndDeviceSupportStackStatusCallback(EmberStatus status); \
  void emberAfPluginIasZoneServerStackStatusCallback(EmberStatus status); \
  void emberAfPluginNetworkFindStackStatusCallback(EmberStatus status); \
  void emberAfPluginSecuritySensorStackStatusCallback(EmberStatus status); \


#define EMBER_AF_GENERATED_PLUGIN_STACK_STATUS_FUNCTION_CALLS \
  emberAfPluginConnectionManagerStackStatusCallback(status); \
  emberAfPluginEndDeviceSupportStackStatusCallback(status); \
  emberAfPluginIasZoneServerStackStatusCallback(status); \
  emberAfPluginNetworkFindStackStatusCallback(status); \
  emberAfPluginSecuritySensorStackStatusCallback(status); \


#define EMBER_AF_GENERATED_PLUGIN_TICK_FUNCTION_DECLARATIONS \
  void emberAfPluginEndDeviceSupportTickCallback(void); \
  void emberAfPluginIdleSleepTickCallback(void); \


#define EMBER_AF_GENERATED_PLUGIN_TICK_FUNCTION_CALLS \
  emberAfPluginEndDeviceSupportTickCallback(); \
  emberAfPluginIdleSleepTickCallback(); \

// Generated data for the command discovery
#define GENERATED_COMMANDS { \
    { 0x0000, 0x00, COMMAND_MASK_INCOMING_SERVER }, /* Basic / ResetToFactoryDefaults */ \
    { 0x0003, 0x00, COMMAND_MASK_OUTGOING_SERVER | COMMAND_MASK_INCOMING_CLIENT }, /* Identify / IdentifyQueryResponse */ \
    { 0x0003, 0x00, COMMAND_MASK_INCOMING_SERVER }, /* Identify / Identify */ \
    { 0x0003, 0x01, COMMAND_MASK_INCOMING_SERVER }, /* Identify / IdentifyQuery */ \
    { 0x0500, 0x00, COMMAND_MASK_OUTGOING_SERVER }, /* IAS Zone / ZoneStatusChangeNotification */ \
    { 0x0500, 0x00, COMMAND_MASK_INCOMING_SERVER }, /* IAS Zone / ZoneEnrollResponse */ \
    { 0x0500, 0x01, COMMAND_MASK_OUTGOING_SERVER }, /* IAS Zone / ZoneEnrollRequest */ \
  }
#define EMBER_AF_GENERATED_COMMAND_COUNT (7)
#endif // __AF_ENDPOINT_CONFIG__
