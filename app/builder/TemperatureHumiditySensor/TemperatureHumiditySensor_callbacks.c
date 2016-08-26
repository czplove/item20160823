//

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"
#include "app/framework/plugin/ezmode-commissioning/ez-mode.h"
#include "app/framework/plugin/reporting/reporting.h"
#include "app/framework/plugin-soc/connection-manager/connection-manager.h"
#include "app/framework/plugin-soc/low-voltage-shutdown/lv-shutdown.h"
#include "app/framework/plugin-soc/temperature-measurement-server/temperature-measurement-server.h"
#include "hal/micro/led-blink.h"

#define MEASUREMENT_FREQUENCY_MS            (30)
#define BATTERY_VOLTAGE_MIN_THRESHOLD_MASK  0x01
#define BATTERY_VOLTAGE_THRESHOLD1_MASK     0x02
#define BATTERY_VOLTAGE_THRESHOLD2_MASK     0x04
#define BATTERY_VOLTAGE_THRESHOLD3_MASK     0x08
#define ALARM_CLUSTER_ALARM_TABLE_SIZES     0x10

#define REPORTING_CLUSTER_LISTS		0x03
const uint16_t clusterlist[REPORTING_CLUSTER_LISTS] = {
  ZCL_POWER_CONFIG_CLUSTER_ID,
  ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
  ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
};
#define BUTTON_DEBOUNCE_TIME_MS     50
#define MAX_TIME_BETWEEN_PRESSES_MS 600
static uint8_t consecutiveButtonPressCount = 0;
// Custom event stubs. Custom events will be run along with all other events in
// the application framework. They should be managed using the Ember Event API
// documented in stack/include/events.h

// Event control struct declaration
EmberEventControl emberAfButton0PressCountEventControl;

extern uint8_t ForbidJoinNetwork_Model;

// Event function forward declaration
void emberAfButton0PressCountEventHandler(void);

// Event function stub
void emberAfButton0PressCountEventHandler(void)
{
  if (emberAfNetworkState() != EMBER_NO_NETWORK) {
    // If on a network:
    // 2 presses activates identify
    // 3 presses blinks network status
    // 4 presses initiates a proactive rejoin
    if(consecutiveButtonPressCount == 1){
      emberAfPluginConnectionManagerLedNetworkFoundBlink();
    }else if (consecutiveButtonPressCount == 2) {
      emberAfEzmodeServerCommission(emberAfPrimaryEndpoint()); /* ezmode server */
    } else if (consecutiveButtonPressCount == 3) {

    } else if (consecutiveButtonPressCount == 4) {
      emberAfEzmodeClientCommission(emberAfPrimaryEndpoint(),
                                    EMBER_AF_EZMODE_COMMISSIONING_SERVER_TO_CLIENT,
                                    clusterlist,REPORTING_CLUSTER_LISTS);  /* ezmode Client */
    } else if (consecutiveButtonPressCount == 6) {
      emberAfStartMoveCallback();
    }
    ForbidJoinNetwork_Model = 0;
  } else {
    // If not a network, then regardless of button presses or length, we want to
    // make sure we are looking for a network.
    emberAfPluginConnectionManagerResetJoinAttempts();
    if (!emberStackIsPerformingRejoin()) {
      emberAfPluginConnectionManagerLeaveNetworkAndStartSearchForNewOne();
    }
  }

  consecutiveButtonPressCount = 0;
  emberEventControlSetInactive(emberAfButton0PressCountEventControl);

}
/** @brief Button0 Pressed Short
 *
 * This function returns the number of times a button was short pressed.
 *
 * @param timePressedMs Time (in ms) button 0 was pressed  Ver.: always
 */
void emberAfPluginButtonInterfaceButton0PressedShortCallback(uint16_t timePressedMs)
{
  // If the button was not held for longer than the debounce time, ignore the
  // press.
//  if (timePressedMs < BUTTON_DEBOUNCE_TIME_MS) {
//    consecutiveButtonPressCount = 0;
//    return;
//  }
  if(timePressedMs > BUTTON_DEBOUNCE_TIME_MS *20 ){
    consecutiveButtonPressCount = 0;
    return;
  }
  consecutiveButtonPressCount++;

  emberEventControlSetDelayMS(emberAfButton0PressCountEventControl,
                              MAX_TIME_BETWEEN_PRESSES_MS);
}


/** @brief Reset To Factory Defaults
 *
 * This function is called by the Basic server plugin when a request to reset
 * to factory defaults is received. The plugin will reset attributes managed by
 * the framework to their default values. The application should preform any
 * other necessary reset-related operations in this callback, including
 * resetting any externally-stored attributes.
 *
 * @param endpoint   Ver.: always
 */
void emberAfPluginBasicResetToFactoryDefaultsCallback(uint8_t endpoint)
{
  emberAfIdentifyClusterServerInitCallback(endpoint);
}

/** @brief Button0 Pressing
 *
 * This function is periodically called when button 0 is being pressed.
 *
 */
void emberAfPluginButtonInterfaceButton0PressingCallback(void)
{
  emberAfPluginConnectionManagerFactoryReset();
  emberLeaveNetwork();
  ForbidJoinNetwork_Model = 1;

}

/** @brief Main Init
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup. Any
 * code that you would normally put into the top of the application's main()
 * routine should be put into this function. This is called before the clusters,
 * plugins, and the network are initialized so some functionality is not yet
 * available.
        Note: No callback in the Application Framework is
 * associated with resource cleanup. If you are implementing your application on
 * a Unix host where resource cleanup is a consideration, we expect that you
 * will use the standard Posix system calls, including the use of atexit() and
 * handlers for signals such as SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If
 * you use the signal() function to register your signal handler, please mind
 * the returned value which may be an Application Framework function. If the
 * return value is non-null, please make sure that you call the returned
 * function from your handler to avoid negating the resource cleanup of the
 * Application Framework itself.
 *
 */
void emberAfMainInitCallback(void)
{
  halLedBlinkSetActivityLed(BOARDLED0);
  emberAfPluginTemperatureMeasurementServerSetMeasurementRate(MEASUREMENT_FREQUENCY_MS);
}

/** @brief Get Voltage
 *
 * This function is called by the Low Voltage Shutdown plugin just prior to
 * shutting down, allowing the application to get the VDD voltage before the
 * chip goes offline until next reset.
 *
 * @param currentVoltage The voltage (in mV) read from VDD at get voltage time.
 * Ver.: always
 */
void emberAfPluginLowVoltageShutdownGetVoltageCallback(uint16_t currentVoltage)
{
 uint8_t i;
  uint8_t endpoint;
  uint8_t voltageMinThreshold;
  uint8_t batteryAlarmMask;
  uint8_t voltage = currentVoltage/100;
  uint8_t batteryPercentage  = 0;
  if(voltage>24 && voltage < 33 )
  {
    batteryPercentage = (uint8_t)(((float)currentVoltage*2 -4800)/9);
  }
  else if(voltage >= 33)
  {
    batteryPercentage = 0xC8;
  }
  for (i = 0; i < emberAfEndpointCount(); i++) {
    endpoint = emberAfEndpointFromIndex(i);
    if (emberAfContainsServer(endpoint, ZCL_POWER_CONFIG_CLUSTER_ID))
    {
      emberAfWriteServerAttribute(endpoint,
                                  ZCL_POWER_CONFIG_CLUSTER_ID,
                                  ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID,
                                  (uint8_t *) &voltage,
                                  ZCL_INT8U_ATTRIBUTE_TYPE);
      emberAfWriteServerAttribute(endpoint,
                                  ZCL_POWER_CONFIG_CLUSTER_ID,
                                  ZCL_BATTERY_PERCENTAGE_REMAINING_ATTRIBUTE_ID,
                                  (uint8_t *) &batteryPercentage,
                                  ZCL_INT8U_ATTRIBUTE_TYPE);

      emberAfReadServerAttribute(endpoint,
                                 ZCL_POWER_CONFIG_CLUSTER_ID,
                                 ZCL_BATTERY_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE_ID,
                                 (uint8_t *) &voltageMinThreshold,
                                 sizeof(uint8_t));

      emberAfReadServerAttribute(endpoint,
                                 ZCL_POWER_CONFIG_CLUSTER_ID,
                                 ZCL_BATTERY_ALARM_MASK_ATTRIBUTE_ID,
                                 (uint8_t *) &batteryAlarmMask,
                                 sizeof(uint8_t));
    }
  }
}

/** @brief Power Configuration Cluster Server Attribute Changed
 *
 * Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfPowerConfigClusterServerAttributeChangedCallback(int8u endpoint,
                                                             EmberAfAttributeId attributeId)
{
  if (attributeId != ZCL_BATTERY_ALARM_MASK_ATTRIBUTE_ID
      && attributeId != ZCL_BATTERY_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE_ID
        || emberAfCurrentCommand() == NULL) {
          return;
        }
  switch(attributeId)
  {
  case ZCL_BATTERY_ALARM_MASK_ATTRIBUTE_ID :
  case ZCL_BATTERY_VOLTAGE_MIN_THRESHOLD_ATTRIBUTE_ID :
    emberAfPluginLowVoltageShutdownGetVoltage();
    break;
  }
}
/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be notified
 * of changes to the stack status and take appropriate action.  The return code
 * from this callback is ignored by the framework.  The framework will always
 * process the stack status after the callback returns.
 *
 * @param status   Ver.: always
 */
boolean emberAfStackStatusCallback(EmberStatus status)
{
  switch (status)
  {
  case EMBER_NETWORK_UP:
  case EMBER_TRUST_CENTER_EUI_HAS_CHANGED:  // also means NETWORK_UP
//    emberAfEzmodeClientCommission(emberAfPrimaryEndpoint(),
//                                  EMBER_AF_EZMODE_COMMISSIONING_SERVER_TO_CLIENT,
//                                  clusterlist,REPORTING_CLUSTER_LISTS);  /* ezmode Client */
    {
      emberAfPluginTemperatureMeasurementServerSetMeasurementRate(MEASUREMENT_FREQUENCY_MS);
      EmberAfPluginReportingEntry newEntry;
      newEntry.attributeId = ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID;
      newEntry.clusterId = ZCL_POWER_CONFIG_CLUSTER_ID;
      newEntry.data.reported.minInterval = 3600;
      newEntry.data.reported.maxInterval = 43200;
      newEntry.data.reported.reportableChange = 01;
      newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
      newEntry.endpoint = emberAfPrimaryEndpoint();
      newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
      newEntry.mask = CLUSTER_MASK_SERVER;
      emberAfPluginReportingConfigureReportedAttribute(&newEntry);


      newEntry.attributeId = ZCL_TEMP_MEASURED_VALUE_ATTRIBUTE_ID;
      newEntry.clusterId = ZCL_TEMP_MEASUREMENT_CLUSTER_ID;
      newEntry.data.reported.minInterval = 10;
      newEntry.data.reported.maxInterval = 180;
      newEntry.data.reported.reportableChange = 100;
      newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
      newEntry.endpoint = emberAfPrimaryEndpoint();
      newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
      newEntry.mask = CLUSTER_MASK_SERVER;
      emberAfPluginReportingConfigureReportedAttribute(&newEntry);

      newEntry.attributeId = ZCL_RELATIVE_HUMIDITY_MEASURED_VALUE_ATTRIBUTE_ID;
      newEntry.clusterId = ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID;
      newEntry.data.reported.minInterval = 10;
      newEntry.data.reported.maxInterval = 180;
      newEntry.data.reported.reportableChange = 500;
      newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
      newEntry.endpoint = emberAfPrimaryEndpoint();
      newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
      newEntry.mask = CLUSTER_MASK_SERVER;
      emberAfPluginReportingConfigureReportedAttribute(&newEntry);

      newEntry.attributeId = ZCL_LAST_MESSAGE_RSSI_ATTRIBUTE_ID;
      newEntry.clusterId = ZCL_DIAGNOSTICS_CLUSTER_ID;
      newEntry.data.reported.minInterval = 60;
      newEntry.data.reported.maxInterval = 60;
      newEntry.data.reported.reportableChange = 10;
      newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
      newEntry.endpoint = emberAfPrimaryEndpoint();
      newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
      newEntry.mask = CLUSTER_MASK_SERVER;
      emberAfPluginReportingConfigureReportedAttribute(&newEntry);
    }
    emberAfPluginLowVoltageShutdownGetVoltage();
    break;
  }
  return false;
}


/** @brief Configured
 *
 * This callback is called by the Reporting plugin whenever a reporting entry
 * is configured, including when entries are deleted or updated. The
 * application can use this callback for scheduling readings or measurements
 * based on the minimum and maximum reporting interval for the entry. The
 * application should return EMBER_ZCL_STATUS_SUCCESS if it can support the
 * configuration or an error status otherwise. Note: attribute reporting is
 * required for many clusters and attributes, so rejecting a reporting
 * configuration may violate ZigBee specifications.
 *
 * @param entry   Ver.: always
 */
EmberAfStatus emberAfPluginReportingConfiguredCallback(const EmberAfPluginReportingEntry *entry)
{
  return EMBER_ZCL_STATUS_SUCCESS;
}


/** @brief Client Complete
 *
 * This function is called by the EZ-Mode Commissioning plugin when client
 * commissioning completes.
 *
 * @param bindingIndex The binding index that was created or
 * ::EMBER_NULL_BINDING if an error occurred. Ver.: always
 */
void emberAfPluginEzmodeCommissioningClientCompleteCallback(uint8_t bindingIndex)
{
}


