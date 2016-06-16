// This file is generated by Ember Desktop.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __APP_CONTACTSWITCH_H__
#define __APP_CONTACTSWITCH_H__


/**** Included Header Section ****/

/**** ZCL Section ****/
#define ZA_PROMPT "ContactSwitch"
#define ZCL_USING_BASIC_CLUSTER_SERVER
#define ZCL_USING_POWER_CONFIG_CLUSTER_SERVER
#define ZCL_USING_IDENTIFY_CLUSTER_SERVER
#define ZCL_USING_POLL_CONTROL_CLUSTER_SERVER
#define ZCL_USING_IAS_ZONE_CLUSTER_SERVER
/**** Optional Attributes ****/
#define ZCL_USING_BASIC_CLUSTER_APPLICATION_VERSION_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_STACK_VERSION_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_HW_VERSION_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_MANUFACTURER_NAME_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_MODEL_IDENTIFIER_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_DATE_CODE_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_LOCATION_DESCRIPTION_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_PHYSICAL_ENVIRONMENT_ATTRIBUTE 
#define ZCL_USING_BASIC_CLUSTER_DEVICE_ENABLED_ATTRIBUTE 
#define ZCL_USING_POWER_CONFIG_CLUSTER_BATTERY_VOLTAGE_ATTRIBUTE 
#define ZCL_USING_POWER_CONFIG_CLUSTER_BATTERY_ALARM_MASK_ATTRIBUTE 
#define ZCL_USING_POWER_CONFIG_CLUSTER_BATTERY_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE 
#define EMBER_AF_MANUFACTURER_CODE 0x1171
#define EMBER_AF_DEFAULT_RESPONSE_POLICY_NEVER
#define EMBER_AF_HAS_SPEC_VERSIONS_HA_1_2

/**** Cluster endpoint counts ****/
#define EMBER_AF_BASIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_POWER_CONFIG_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_IDENTIFY_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_POLL_CONTROL_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_IAS_ZONE_CLUSTER_SERVER_ENDPOINT_COUNT (1)

/**** CLI Section ****/
#define EMBER_AF_GENERATE_CLI
#define EMBER_COMMAND_INTEPRETER_HAS_DESCRIPTION_FIELD

/**** Security Section ****/
#define EMBER_AF_HAS_SECURITY_PROFILE_HA

/**** Network Section ****/
#define EMBER_SUPPORTED_NETWORKS (1)
#define EMBER_AF_NETWORK_INDEX_PRIMARY (0)
#define EMBER_AF_DEFAULT_NETWORK_INDEX EMBER_AF_NETWORK_INDEX_PRIMARY
#define EMBER_AF_HAS_END_DEVICE_NETWORK
#define EMBER_AF_HAS_SLEEPY_NETWORK
#define EMBER_AF_TX_POWER_MODE EMBER_TX_POWER_MODE_BOOST
#define EMBER_AF_ENABLE_TX_ZDO

/**** HAL Section ****/
#define ZA_CLI_FULL

/**** Callback Section ****/
#define EMBER_CALLBACK_MAIN_INIT
#define EMBER_CALLBACK_STACK_STATUS
#define EMBER_CALLBACK_POWER_CONFIG_CLUSTER_POWER_CONFIG_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_BASIC_CLUSTER_RESET_TO_FACTORY_DEFAULTS
#define EMBER_CALLBACK_HAL_BUTTON_ISR
#define EMBER_CALLBACK_POLL_COMPLETE
#define EMBER_APPLICATION_HAS_POLL_COMPLETE_HANDLER
#define EMBER_CALLBACK_PRE_NCP_RESET
#define EMBER_CALLBACK_EZSP_POLL_COMPLETE
#define EZSP_APPLICATION_HAS_POLL_COMPLETE_HANDLER
#define EMBER_CALLBACK_ADD_TO_CURRENT_APP_TASKS
#define EMBER_CALLBACK_REMOVE_FROM_CURRENT_APP_TASKS
#define EMBER_CALLBACK_GET_CURRENT_APP_TASKS
#define EMBER_CALLBACK_GET_LONG_POLL_INTERVAL_MS
#define EMBER_CALLBACK_GET_LONG_POLL_INTERVAL_QS
#define EMBER_CALLBACK_SET_LONG_POLL_INTERVAL_MS
#define EMBER_CALLBACK_SET_LONG_POLL_INTERVAL_QS
#define EMBER_CALLBACK_GET_SHORT_POLL_INTERVAL_MS
#define EMBER_CALLBACK_GET_SHORT_POLL_INTERVAL_QS
#define EMBER_CALLBACK_SET_SHORT_POLL_INTERVAL_MS
#define EMBER_CALLBACK_SET_SHORT_POLL_INTERVAL_QS
#define EMBER_CALLBACK_GET_CURRENT_POLL_INTERVAL_MS
#define EMBER_CALLBACK_GET_CURRENT_POLL_INTERVAL_QS
#define EMBER_CALLBACK_GET_WAKE_TIMEOUT_MS
#define EMBER_CALLBACK_GET_WAKE_TIMEOUT_QS
#define EMBER_CALLBACK_SET_WAKE_TIMEOUT_MS
#define EMBER_CALLBACK_SET_WAKE_TIMEOUT_QS
#define EMBER_CALLBACK_GET_WAKE_TIMEOUT_BITMASK
#define EMBER_CALLBACK_SET_WAKE_TIMEOUT_BITMASK
#define EMBER_CALLBACK_GET_CURRENT_POLL_CONTROL
#define EMBER_CALLBACK_GET_DEFAULT_POLL_CONTROL
#define EMBER_CALLBACK_SET_DEFAULT_POLL_CONTROL
#define EMBER_CALLBACK_START_MOVE
#define EMBER_CALLBACK_STOP_MOVE
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_PRE_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_RESPONSE
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY
#define EMBER_CALLBACK_GET_CURRENT_SLEEP_CONTROL
#define EMBER_CALLBACK_GET_DEFAULT_SLEEP_CONTROL
#define EMBER_CALLBACK_SET_DEFAULT_SLEEP_CONTROL
#define EMBER_CALLBACK_UNUSED_PAN_ID_FOUND
#define EMBER_CALLBACK_SCAN_ERROR
#define EMBER_CALLBACK_FIND_UNUSED_PAN_ID_AND_FORM
#define EMBER_CALLBACK_START_SEARCH_FOR_JOINABLE_NETWORK
#define EMBER_CALLBACK_GET_FORM_AND_JOIN_EXTENDED_PAN_ID
#define EMBER_CALLBACK_SET_FORM_AND_JOIN_EXTENDED_PAN_ID
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_POLL_CONTROL_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_POLL_CONTROL_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_POLL_CONTROL_CLUSTER_SERVER_PRE_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_POLL_CONTROL_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_CHECK_IN_RESPONSE
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_FAST_POLL_STOP
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_SET_LONG_POLL_INTERVAL
#define EMBER_CALLBACK_POLL_CONTROL_CLUSTER_SET_SHORT_POLL_INTERVAL
#define EMBER_CALLBACK_CONFIGURE_REPORTING_COMMAND
#define EMBER_CALLBACK_READ_REPORTING_CONFIGURATION_COMMAND
#define EMBER_CALLBACK_CLEAR_REPORT_TABLE
#define EMBER_CALLBACK_REPORTING_ATTRIBUTE_CHANGE
/**** Debug printing section ****/

// Global switch
// #define EMBER_AF_PRINT_ENABLE
// Individual areas
#define EMBER_AF_PRINT_CORE 0x0001
#define EMBER_AF_PRINT_APP 0x0002
#define EMBER_AF_PRINT_ATTRIBUTES 0x0004
#define EMBER_AF_PRINT_POLL_CONTROL_CLUSTER 0x0008
#define EMBER_AF_PRINT_BITS { 0x0F }
#define EMBER_AF_PRINT_NAMES { \
  "Core",\
  "Application",\
  "Attributes",\
  "Poll Control",\
  NULL\
}
#define EMBER_AF_PRINT_NAME_NUMBER 4


#define EMBER_AF_SUPPORT_COMMAND_DISCOVERY


// Generated plugin macros

// Use this macro to check if Address Table plugin is included
#define EMBER_AF_PLUGIN_ADDRESS_TABLE
// User options for plugin Address Table
#define EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE 4
#define EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE 2

// Use this macro to check if Basic Server Cluster plugin is included
#define EMBER_AF_PLUGIN_BASIC

// Use this macro to check if Ember Minimal Printf plugin is included
#define EMBER_AF_PLUGIN_EMBER_MINIMAL_PRINTF

// Use this macro to check if End Device Support plugin is included
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT
// User options for plugin End Device Support
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT_SHORT_POLL_INTERVAL_SECONDS 1
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT_LONG_POLL_INTERVAL_SECONDS 20
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT_WAKE_TIMEOUT_SECONDS 1
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT_WAKE_TIMEOUT_BITMASK 24
#define EMBER_AF_PLUGIN_END_DEVICE_SUPPORT_MAX_MISSED_POLLS 4
#define EMBER_AF_REJOIN_ATTEMPTS_MAX 10

// Use this macro to check if EZ-Mode Commissioning plugin is included
#define EMBER_AF_PLUGIN_EZMODE_COMMISSIONING
// User options for plugin EZ-Mode Commissioning
#define EMBER_AF_PLUGIN_EZMODE_COMMISSIONING_IDENTIFY_TIMEOUT 180

// Use this macro to check if Form and Join Library plugin is included
#define EMBER_AF_PLUGIN_FORM_AND_JOIN

// Use this macro to check if IAS Zone Server plugin is included
#define EMBER_AF_PLUGIN_IAS_ZONE_SERVER
// User options for plugin IAS Zone Server
#define EMBER_AF_PLUGIN_IAS_ZONE_SERVER_ZONE_TYPE 21

// Use this macro to check if Identify Cluster plugin is included
#define EMBER_AF_PLUGIN_IDENTIFY

// Use this macro to check if Network Find plugin is included
#define EMBER_AF_PLUGIN_NETWORK_FIND
#define EMBER_AF_DISABLE_FORM_AND_JOIN_TICK
// User options for plugin Network Find
#define EMBER_AF_PLUGIN_NETWORK_FIND_CHANNEL_MASK 0x07FFF800UL
#define EMBER_AF_PLUGIN_NETWORK_FIND_RADIO_TX_POWER 8
#define EMBER_AF_PLUGIN_NETWORK_FIND_RADIO_TX_CALLBACK
#define EMBER_AF_PLUGIN_NETWORK_FIND_EXTENDED_PAN_ID { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define EMBER_AF_PLUGIN_NETWORK_FIND_DURATION 5
#define EMBER_AF_PLUGIN_NETWORK_FIND_JOINABLE_SCAN_TIMEOUT_MINUTES 1

// Use this macro to check if Poll Control Server Cluster plugin is included
#define EMBER_AF_PLUGIN_POLL_CONTROL_SERVER
// User options for plugin Poll Control Server Cluster
#define EMBER_AF_PLUGIN_POLL_CONTROL_SERVER_MAX_CLIENTS 4
#define EMBER_AF_PLUGIN_POLL_CONTROL_SERVER_CHECK_IN_RESPONSE_TIMEOUT 240
#define EMBER_AF_PLUGIN_POLL_CONTROL_SERVER_ACCEPT_SET_LONG_POLL_INTERVAL_COMMAND
#define EMBER_AF_PLUGIN_POLL_CONTROL_SERVER_ACCEPT_SET_SHORT_POLL_INTERVAL_COMMAND

// Use this macro to check if Reporting plugin is included
#define EMBER_AF_PLUGIN_REPORTING
// User options for plugin Reporting
#define EMBER_AF_PLUGIN_REPORTING_TABLE_SIZE 5

// Use this macro to check if Simple Main plugin is included
#define EMBER_AF_PLUGIN_SIMPLE_MAIN

// Use this macro to check if Connection Manager plugin is included
#define EMBER_AF_PLUGIN_CONNECTION_MANAGER
// User options for plugin Connection Manager
#define EMBER_AF_PLUGIN_CONNECTION_MANAGER_REJOIN_TIME_M 15
#define EMBER_AF_PLUGIN_CONNECTION_MANAGER_RETRY_TIME_S 5
#define EMBER_AF_PLUGIN_CONNECTION_MANAGER_REJOIN_ATTEMPTS 20

// Use this macro to check if Idle/Sleep plugin is included
#define EMBER_AF_PLUGIN_IDLE_SLEEP
// User options for plugin Idle/Sleep
#define EMBER_AF_PLUGIN_IDLE_SLEEP_MINIMUM_SLEEP_DURATION_MS 5

// Use this macro to check if Low Voltage Shutdown plugin is included
#define EMBER_AF_PLUGIN_LOW_VOLTAGE_SHUTDOWN
// User options for plugin Low Voltage Shutdown
#define EMBER_AF_PLUGIN_LOW_VOLTAGE_SHUTDOWN_SHUTDOWN_CHECK_DURATION_MINUTES 30
#define EMBER_AF_PLUGIN_LOW_VOLTAGE_SHUTDOWN_SHUTDOWN_POSTPONE_DURATION_MS 500
#define EMBER_AF_PLUGIN_LOW_VOLTAGE_SHUTDOWN_VDD_LOW_THRESHOLD 2100

// Use this macro to check if Manufacturing Library CLI plugin is included
#define EMBER_AF_PLUGIN_MANUFACTURING_LIBRARY_CLI

// Use this macro to check if Security Sensor Interface plugin is included
#define EMBER_AF_PLUGIN_SECURITY_SENSOR
// User options for plugin Security Sensor Interface
#define EMBER_AF_PLUGIN_SECURITY_SENSOR_NETWORK_LEAVE_TIME_MS 6000
#define EMBER_AF_PLUGIN_SECURITY_SENSOR_BUTTON_DEBOUNCE_TIME_MS 50
#define EMBER_AF_PLUGIN_SECURITY_SENSOR_IAS_ZONE_ENDPOINT 1
#define EMBER_AF_PLUGIN_SECURITY_SENSOR_TIME_BETWEEN_PRESSES_MS 600

// Use this macro to check if Alarm Library plugin is included
#define EMBER_AF_PLUGIN_ALARM_LIBRARY

// Use this macro to check if Binding Table Library plugin is included
#define EMBER_AF_PLUGIN_BINDING_TABLE_LIBRARY
// User options for plugin Binding Table Library
#define EMBER_BINDING_TABLE_SIZE 4

// Use this macro to check if Debug Basic Library plugin is included
#define EMBER_AF_PLUGIN_DEBUG_BASIC_LIBRARY

// Use this macro to check if Manufacturing Library plugin is included
#define EMBER_AF_PLUGIN_MANUFACTURING_LIBRARY

// Use this macro to check if Packet Validate Library plugin is included
#define EMBER_AF_PLUGIN_PACKET_VALIDATE_LIBRARY

// Use this macro to check if Security Core Library plugin is included
#define EMBER_AF_PLUGIN_SECURITY_LIBRARY_CORE
// User options for plugin Security Core Library
#define EMBER_TRANSIENT_KEY_TIMEOUT_S 300

// Use this macro to check if ZigBee PRO Stack Library plugin is included
#define EMBER_AF_PLUGIN_ZIGBEE_PRO_LIBRARY
// User options for plugin ZigBee PRO Stack Library
#define EMBER_MAX_END_DEVICE_CHILDREN 6
#define EMBER_PACKET_BUFFER_COUNT 75
#define EMBER_END_DEVICE_POLL_TIMEOUT 5
#define EMBER_END_DEVICE_POLL_TIMEOUT_SHIFT 6
#define EMBER_APS_UNICAST_MESSAGE_COUNT 10

// Use this macro to check if Antenna Stub plugin is included
#define EMBER_AF_PLUGIN_ANTENNA_STUB

// Use this macro to check if Button Interface plugin is included
#define EMBER_AF_PLUGIN_BUTTON_INTERFACE
// User options for plugin Button Interface
#define EMBER_AF_PLUGIN_BUTTON_INTERFACE_BUTTON_TIMEOUT_MS 1000

// Use this macro to check if Generic GPIO Interrupt Controller plugin is included
#define EMBER_AF_PLUGIN_GENERIC_INTERRUPT_CONTROL

// Use this macro to check if GPIO Sensor Interface plugin is included
#define EMBER_AF_PLUGIN_GPIO_SENSOR
// User options for plugin GPIO Sensor Interface
#define EMBER_AF_PLUGIN_GPIO_SENSOR_SENSOR_POLARITY 1
#define EMBER_AF_PLUGIN_GPIO_SENSOR_ASSERT_DEBOUNCE 100
#define EMBER_AF_PLUGIN_GPIO_SENSOR_DEASSERT_DEBOUNCE 100

// Use this macro to check if HAL Library plugin is included
#define EMBER_AF_PLUGIN_HAL_LIBRARY

// Use this macro to check if LED Blinking plugin is included
#define EMBER_AF_PLUGIN_LED_BLINK

// Use this macro to check if Simulated EEPROM version 1 Library plugin is included
#define EMBER_AF_PLUGIN_SIM_EEPROM1

// Use this macro to check if Tamper Switch Interface plugin is included
#define EMBER_AF_PLUGIN_TAMPER_SWITCH
// User options for plugin Tamper Switch Interface
#define EMBER_AF_PLUGIN_TAMPER_SWITCH_TAMPER_POLARITY 0


// Generated API headers

// API antenna from Antenna Stub plugin
#define EMBER_AF_API_ANTENNA "hal/micro/antenna.h"


// Custom macros
#ifdef APP_SERIAL
#undef APP_SERIAL
#endif
#define APP_SERIAL 1

#ifdef EMBER_ASSERT_SERIAL_PORT
#undef EMBER_ASSERT_SERIAL_PORT
#endif
#define EMBER_ASSERT_SERIAL_PORT 1

#ifdef EMBER_AF_BAUD_RATE
#undef EMBER_AF_BAUD_RATE
#endif
#define EMBER_AF_BAUD_RATE 115200

#ifdef EMBER_SERIAL1_MODE
#undef EMBER_SERIAL1_MODE
#endif
#define EMBER_SERIAL1_MODE EMBER_SERIAL_FIFO

#ifdef EMBER_SERIAL1_RX_QUEUE_SIZE
#undef EMBER_SERIAL1_RX_QUEUE_SIZE
#endif
#define EMBER_SERIAL1_RX_QUEUE_SIZE 128

#ifdef EMBER_SERIAL1_TX_QUEUE_SIZE
#undef EMBER_SERIAL1_TX_QUEUE_SIZE
#endif
#define EMBER_SERIAL1_TX_QUEUE_SIZE 128

#ifdef EMBER_SERIAL1_BLOCKING
#undef EMBER_SERIAL1_BLOCKING
#endif
#define EMBER_SERIAL1_BLOCKING

#ifdef EMBER_AF_SERIAL_PORT_INIT
#undef EMBER_AF_SERIAL_PORT_INIT
#endif
#define EMBER_AF_SERIAL_PORT_INIT() \
  do { \
    emberSerialInit(1, BAUD_115200, PARITY_NONE, 1); \
  } while (0)



#endif // __APP_CONTACTSWITCH_H__
