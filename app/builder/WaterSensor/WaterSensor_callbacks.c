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
#include "hal/micro/led-blink.h"
#include "hal/micro/gpio-sensor.h"
#include "hal/micro/led.h"

#define BATTERY_VOLTAGE_MIN_THRESHOLD_MASK      0x01
#define REPORTING_CLUSTER_LISTS		            0x01
const uint16_t clusterlist[REPORTING_CLUSTER_LISTS] = {
  ZCL_POWER_CONFIG_CLUSTER_ID,
};
static HalLowBatteryState lastBatteryStatus = HAL_LOW_BATTERY_NOT_ACTIVE;
static HalLowBatteryState newBatteryStatus = HAL_LOW_BATTERY_NOT_ACTIVE;

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
  for (i = 0; i < emberAfEndpointCount(); i++) {
    endpoint = emberAfEndpointFromIndex(i);
    if (emberAfContainsServer(endpoint, ZCL_POWER_CONFIG_CLUSTER_ID))
    {
      emberAfWriteServerAttribute(endpoint,
                                  ZCL_POWER_CONFIG_CLUSTER_ID,
                                  ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID,
                                  (uint8_t *) &voltage,
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
      if((voltage < voltageMinThreshold) &&
         (batteryAlarmMask &BATTERY_VOLTAGE_MIN_THRESHOLD_MASK))
      {
        newBatteryStatus = HAL_LOW_BATTERY_ACTIVE;
        if(lastBatteryStatus != newBatteryStatus)
        {
          lastBatteryStatus = newBatteryStatus;
          emberAfPluginBatteryMonitorLowVoltageCallback(newBatteryStatus);
        }
      }
      else
      {
        newBatteryStatus = HAL_LOW_BATTERY_NOT_ACTIVE;
        if(lastBatteryStatus != newBatteryStatus)
        {
          lastBatteryStatus = newBatteryStatus;
          emberAfPluginBatteryMonitorLowVoltageCallback(newBatteryStatus);
        }
      }
    }
  }
}

/** @brief Get Radio Power For Channel
 *
 * This callback is called by the framework when it is setting the radio power
 * during the discovery process. The framework will set the radio power
 * depending on what is returned by this callback.
 *
 * @param channel   Ver.: always
 */
int8_t emberAfPluginNetworkFindGetRadioPowerForChannelCallback(uint8_t channel)
{
  return EMBER_AF_PLUGIN_NETWORK_FIND_RADIO_TX_POWER;
}

/** @brief Join
 *
 * This callback is called by the plugin when a joinable network has been
 * found. If the application returns true, the plugin will attempt to join the
 * network. Otherwise, the plugin will ignore the network and continue
 * searching. Applications can use this callback to implement a network
 * blacklist.
 *
 * @param networkFound   Ver.: always
 * @param lqi   Ver.: always
 * @param rssi   Ver.: always
 */
bool emberAfPluginNetworkFindJoinCallback(EmberZigbeeNetwork *networkFound,
                                          uint8_t lqi,
                                          int8_t rssi)
{
  return true;
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


/** @brief Poll Completed
 *
 * This function is called by the End Device Support plugin after a poll is
 * completed.
 *
 * @param status Return status of a completed poll operation Ver.: always
 */
void emberAfPluginEndDeviceSupportPollCompletedCallback(EmberStatus status)
{
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
    emberAfPluginLowVoltageShutdownGetVoltage();
    break;
  }
  return false;
}

/** @brief Button0 Pressing
 *
 * This function is periodically called when button 0 is being pressed.
 *
 */
void emberAfPluginButtonInterfaceButton0PressingCallback(void)
{
  emberAfAppPrintln("   > LEAVE NETWORK");
  emberAfPluginConnectionManagerLeaveNetworkAndStartSearchForNewOne();
  emberAfPluginConnectionManagerFactoryReset();
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
