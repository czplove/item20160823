//

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"
#include "app/framework/include/af-types.h"
#include "app/framework/util/common.h"
#include "app/framework/plugin/reporting/reporting.h"
#include "app/framework/plugin/ezmode-commissioning/ez-mode.h"
#include "app/framework/plugin-soc/connection-manager/connection-manager.h"
#include "app/framework/plugin/on-off/on-off.h"
#include "hal/micro/led-blink.h"
#include "stack/include/ember-types.h"
#include "MAX71020.h"

#define RelayOutOn()  halClearLed(BOARDRELAY_CONTROL)
#define RelayOutOff() halSetLed(BOARDRELAY_CONTROL)
static void userAppLoadOpen(void);
static void userAppLoadClose(void);
#define REPORTING_CLUSTER_LISTS		0x02
const uint16_t clusterlist[REPORTING_CLUSTER_LISTS] = {ZCL_ON_OFF_CLUSTER_ID,ZCL_SIMPLE_METERING_CLUSTER_ID};

#define BUTTON_DEBOUNCE_TIME_MS     50
#define MAX_TIME_BETWEEN_PRESSES_MS 600
static uint8_t consecutiveButtonPressCount = 0;
// Custom event stubs. Custom events will be run along with all other events in
// the application framework. They should be managed using the Ember Event API
// documented in stack/include/events.h

// Event control struct declaration
EmberEventControl emberAfButton0PressCountEventControl;

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
      //      emberAfStartMoveCallback();
    }
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
  MAX71020_AFE_ResetDefault();
  MAX71020_AFE_RestoreMeteringPara(&MeteringPara);
  halLedBlinkSetActivityLed(BOARDLED0);
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
  bool currentValue;
  emberAfIdentifyClusterServerInitCallback(endpoint);
  emberAfReadAttribute(endpoint,
                                ZCL_ON_OFF_CLUSTER_ID,
                                ZCL_ON_OFF_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (uint8_t *)&currentValue,
                                sizeof(currentValue),
                                NULL); // data type
  if(currentValue == ZCL_OFF_COMMAND_ID)
    userAppLoadClose();
  MAX71020_AFE_SetDefaultMeteringPara(&MeteringPara);
  MAX71020_AFE_StoreMeteringPara(&MeteringPara);

}

/** @brief Button0 High
 *
 * This function is called when the GPIO tied to button zero goes high
 *
 */
void emberAfPluginButtonInterfaceButton0HighCallback(void)
{

}

/** @brief Button0 Low
 *
 * This function is called when the GPIO tied to button zero goes low
 *
 */
void emberAfPluginButtonInterfaceButton0LowCallback(void)
{

}

/** @brief Button0 Pressed Long
 *
 * This function returns the number of times a button was short pressed.
 *
 * @param timePressedMs Amount of time button 0 was pressed.  Ver.: always
 * @param pressedAtReset Was the button pressed at startup.  Ver.: always
 */
void emberAfPluginButtonInterfaceButton0PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{

}


/** @brief Button0 Pressed Short
 *
 * This function returns the number of times a button was short pressed.
 *
 * @param timePressedMs Time (in ms) button 0 was pressed  Ver.: always
 */
void emberAfPluginButtonInterfaceButton0PressedShortCallback(uint16_t timePressedMs)
{
  if(timePressedMs > BUTTON_DEBOUNCE_TIME_MS *20 ){
    consecutiveButtonPressCount = 0;
    return;
  }
  consecutiveButtonPressCount++;

  emberEventControlSetDelayMS(emberAfButton0PressCountEventControl,
                              MAX_TIME_BETWEEN_PRESSES_MS);
}

/** @brief Button0 Pressing
 *
 * This function is periodically called when button 0 is being pressed.
 *
 */
void emberAfPluginButtonInterfaceButton0PressingCallback(void)
{
  bool currentValue;
  emberAfPluginConnectionManagerFactoryReset();
  emberAfReadAttribute(emberAfPrimaryEndpoint(),
                                ZCL_ON_OFF_CLUSTER_ID,
                                ZCL_ON_OFF_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                (uint8_t *)&currentValue,
                                sizeof(currentValue),
                                NULL); // data type
  if(currentValue == ZCL_OFF_COMMAND_ID)
    userAppLoadClose();
  MAX71020_AFE_SetDefaultMeteringPara(&MeteringPara);
  MAX71020_AFE_StoreMeteringPara(&MeteringPara);
  emberLeaveNetwork();
}

/** @brief Button1 Low
 *
 * This function is called when the GPIO tied to button one goes low
 *
 */
void emberAfPluginButtonInterfaceButton1LowCallback(void)
{
  if(halButtonPinState(BUTTON1) ==BUTTON_PRESSED &&halButtonPinState(BUTTON0) ==BUTTON_PRESSED)
  {
    emberAfSendEndDeviceBind(emberAfPrimaryEndpoint());
  }
}
/** @brief Button1 High
 *
 * This function is called when the GPIO tied to button one goes high
 *
 */
void emberAfPluginButtonInterfaceButton1HighCallback(void)
{

}

/** @brief Button1 Pressed Long
 *
 * This function returns the number of times a button was short pressed.
 *
 * @param timePressedMs Amount of time button 1 was pressed.  Ver.: always
 * @param pressedAtReset Was the button pressed at startup.  Ver.: always
 */
void emberAfPluginButtonInterfaceButton1PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{

}

/** @brief Button1 Pressed Short
 *
 * This function returns the number of times a button was short pressed.
 *
 * @param timePressedMs Time (in ms) button 1 was pressed  Ver.: always
 */
void emberAfPluginButtonInterfaceButton1PressedShortCallback(uint16_t timePressedMs)
{
  int8u OnOffState;
  if( halButtonPinState(BUTTON0) == BUTTON_RELEASED )
    if (timePressedMs < 800 && timePressedMs > 50) /* if button is short press < 600ms, control the load on/off */
    {
      emberAfReadServerAttribute(emberAfPrimaryEndpoint(),
                                 ZCL_ON_OFF_CLUSTER_ID,
                                 ZCL_ON_OFF_ATTRIBUTE_ID,
                                 (int8u*)&OnOffState,
                                 sizeof(int8u));
      if(OnOffState)
        OnOffState = 0;
      else if(!OnOffState)
        OnOffState = 1;
      emberAfWriteServerAttribute(emberAfPrimaryEndpoint(),
                                  ZCL_ON_OFF_CLUSTER_ID,
                                  ZCL_ON_OFF_ATTRIBUTE_ID,
                                  (int8u*)&OnOffState,
                                  ZCL_BOOLEAN_ATTRIBUTE_TYPE);
    }
}

/** @brief Button1 Pressing
 *
 * This function is periodically called when button 1 is being pressed.
 *
 */
void emberAfPluginButtonInterfaceButton1PressingCallback(void)
{

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

/** @brief Post Attribute Change
 *
 * This function is called by the application framework after it changes an
 * attribute value. The value passed into this callback is the value to which
 * the attribute was set by the framework.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param type   Ver.: always
 * @param size   Ver.: always
 * @param value   Ver.: always
 */
void emberAfPostAttributeChangeCallback(int8u endpoint,
                                        EmberAfClusterId clusterId,
                                        EmberAfAttributeId attributeId,
                                        int8u mask,
                                        int16u manufacturerCode,
                                        int8u type,
                                        int8u size,
                                        int8u* value)
{
}

/** @brief Basic Cluster Server Attribute Changed
 *
 * Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfBasicClusterServerAttributeChangedCallback(int8u endpoint,
                                                       EmberAfAttributeId attributeId)
{
}

/** @brief Simple Metering Cluster Get Profile
 *
 * 
 *
 * @param intervalChannel   Ver.: always
 * @param endTime   Ver.: always
 * @param numberOfPeriods   Ver.: always
 */
boolean emberAfSimpleMeteringClusterGetProfileCallback(int8u intervalChannel,
                                                       int32u endTime,
                                                       int8u numberOfPeriods)
{
  emberAfFillCommandSimpleMeteringClusterGetProfileResponse(endTime,
                                                            0x05,
                                                            0,
                                                            0,
                                                            appResponseData,
                                                            0);
  appResponseData[1] = emberAfIncomingZclSequenceNumber;
  appResponseLength = 10;
  emberAfSendResponse();
  return true;
}

/** @brief Simple Metering Cluster Server Tick
 *
 * Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfSimpleMeteringClusterServerTickCallback(int8u endpoint)
{

  uint8_t dataType;
  EmberAfStatus status;
  int8u summation[] = {0,0,0,0,0,0};
  int8u*p = summation;
  int64u Summation;
  MAX71020_AFE_Metering_t *pMeter;
  uint8_t ep = emberAfFindClusterServerEndpointIndex(endpoint,
                                                     ZCL_SIMPLE_METERING_CLUSTER_ID);
  if (ep == 0xFF) {
    emberAfSimpleMeteringClusterPrintln("Invalid endpoint %x", endpoint);
    return;
  }
  // Now let's adjust the summation
  status = emberAfReadAttribute(endpoint,
                                ZCL_SIMPLE_METERING_CLUSTER_ID,
                                ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID,
                                CLUSTER_MASK_SERVER,
                                summation,
                                6,
                                &dataType);

  if ( status != EMBER_ZCL_STATUS_SUCCESS ) {
    emberAfSimpleMeteringClusterPrintln("ERR: can't read summation status 0x%x",status);
    return;
  }
  pMeter = MAX71020_AFE_GetAllMeteringData();
  emberAfSimpleMeteringClusterPrintln("Voltage %10d mV",pMeter->voltage);
  emberAfSimpleMeteringClusterPrintln("Current %10d mA",pMeter->current);
  emberAfSimpleMeteringClusterPrintln("Power %10d mW",pMeter->power);
  emberAfSimpleMeteringClusterPrintln("Accumulate Power %10d00mWh",pMeter->accupower);
  Summation = pMeter->accupower;
  UINT48_TO_BUF_LITTLE_ENDIAN(p,Summation);

  emberAfSimpleMeteringClusterPrintln(" ");

  emberAfWriteAttribute(endpoint,
                        ZCL_SIMPLE_METERING_CLUSTER_ID,
                        ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID,
                        CLUSTER_MASK_SERVER,
                        summation,
                        ZCL_INT48U_ATTRIBUTE_TYPE);

  emberAfScheduleServerTick(endpoint,
                            ZCL_SIMPLE_METERING_CLUSTER_ID,
                            MILLISECOND_TICKS_PER_QUARTERSECOND);
}

/** @brief Simple Metering Cluster Server Init
 *
 * Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfSimpleMeteringClusterServerInitCallback(int8u endpoint)
{
  emberAfScheduleServerTick(endpoint,
                            ZCL_SIMPLE_METERING_CLUSTER_ID,
                            MILLISECOND_TICKS_PER_QUARTERSECOND);
}


/** @brief Finished
 *
 * This callback is fired when the Connection Manager plugin is finished with
 * the forming or joining process. The result of the operation will be returned
 * in the status parameter.
 *
 * @param status   Ver.: always
 */
void emberAfPluginConnectionManagerFinishedCallback(EmberStatus status)
{
}

/** @brief On/off Cluster Server Attribute Changed
 *
 * Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffClusterServerAttributeChangedCallback(int8u endpoint,
                                                       EmberAfAttributeId attributeId)
{
  int8u OnOff;
  EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;
  if(endpoint == emberAfPrimaryEndpoint()&& attributeId == ZCL_ON_OFF_ATTRIBUTE_ID)
    status = emberAfReadServerAttribute(endpoint,
                                        ZCL_ON_OFF_CLUSTER_ID,
                                        ZCL_ON_OFF_ATTRIBUTE_ID,
                                        (int8u*)&OnOff,
                                        sizeof(int8u));
  if(status != EMBER_ZCL_STATUS_SUCCESS)
  {
    return ;

  }
  else
  {
    if(OnOff == ZCL_ON_COMMAND_ID)
      userAppLoadOpen();
    else if(OnOff == ZCL_OFF_COMMAND_ID)
      userAppLoadClose();
  }
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
    EmberAfPluginReportingEntry newEntry;
    EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;

    newEntry.attributeId = ZCL_ON_OFF_ATTRIBUTE_ID;
    newEntry.clusterId = ZCL_ON_OFF_CLUSTER_ID;
    newEntry.data.reported.minInterval = 1;
    newEntry.data.reported.maxInterval = 60;
    newEntry.data.reported.reportableChange = 0;
    newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
    newEntry.endpoint = emberAfPrimaryEndpoint();
    newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
    newEntry.mask = CLUSTER_MASK_SERVER;
    status = emberAfPluginReportingConfigureReportedAttribute(&newEntry);
    if(status == EMBER_ZCL_STATUS_SUCCESS)
      emberAfReportingPrintln("%p Cluster :0x%2x Attribute:0x%2x",
                              "Configure Reporting", newEntry.clusterId, newEntry.attributeId);

    newEntry.attributeId = ZCL_CURRENT_SUMMATION_DELIVERED_ATTRIBUTE_ID;
    newEntry.clusterId = ZCL_SIMPLE_METERING_CLUSTER_ID;
    newEntry.data.reported.minInterval = 5;
    newEntry.data.reported.maxInterval = 60;
    newEntry.data.reported.reportableChange = 100;
    newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
    newEntry.endpoint = emberAfPrimaryEndpoint();
    newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
    newEntry.mask = CLUSTER_MASK_SERVER;
    status = emberAfPluginReportingConfigureReportedAttribute(&newEntry);
    if(status == EMBER_ZCL_STATUS_SUCCESS)
      emberAfReportingPrintln("%p Cluster :0x%2x Attribute:0x%2x",
                              "Configure Reporting", newEntry.clusterId, newEntry.attributeId);

    newEntry.attributeId = ZCL_IDENTIFY_TIME_ATTRIBUTE_ID;
    newEntry.clusterId = ZCL_IDENTIFY_CLUSTER_ID;
    newEntry.data.reported.minInterval = 0xFFFF;
    newEntry.data.reported.maxInterval = 0xFFFF;
    newEntry.data.reported.reportableChange = 0xFFFF;
    newEntry.direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED;
    newEntry.endpoint = emberAfPrimaryEndpoint();
    newEntry.manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE;
    newEntry.mask = CLUSTER_MASK_SERVER;
    status = emberAfPluginReportingConfigureReportedAttribute(&newEntry);
    if(status == EMBER_ZCL_STATUS_SUCCESS)
      emberAfReportingPrintln("%p Cluster :0x%2x Attribute:0x%2x",
                              "Configure Reporting", newEntry.clusterId, newEntry.attributeId);
    break;
  }
  return false;
}
/** @brief open the load
 *
 *
 *
 */
void userAppLoadOpen(void)
{
  RelayOutOn();
  halSetLed(BOARDLED1);
}
/** @brief Close the load
 *
 *
 *
 */
void userAppLoadClose(void)
{
  RelayOutOff();
  halClearLed(BOARDLED1);
}


