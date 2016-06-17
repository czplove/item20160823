//

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"
#include "app/framework/plugin/ezmode-commissioning/ez-mode.h"
#include "app/framework/plugin/reporting/reporting.h"
#include "app/framework/plugin-soc/connection-manager/connection-manager.h"
#include "hal/micro/buzzer.h"
#include "hal/micro/led-blink.h"
#include "hal/micro/gpio-sensor.h"

// Custom event stubs. Custom events will be run along with all other events in
// the application framework. They should be managed using the Ember Event API
// documented in stack/include/events.h

// Event control struct declarations
EmberEventControl emberAfUserAppStartWarningEventControl;
EmberEventControl emberAfUserAppStartWarningTimeoutEventControl;
typedef struct
{
  uint8_t mode:4;
  uint8_t strobe:2;
  uint8_t sirenLevel:2;
}WarningInfo_t;

#define WD_MODE_STOP_WARNING                0x00
#define WD_MODE_BURGLAR_WARNING             0x01
#define WD_MODE_FIRE_WARNING                0x02
#define WD_MODE_EMERGENCY_WARNING           0x03
#define WD_MODE_POLICE_PANIC_WARNING        0x04
#define WD_MODE_FIRE_PANIC_WARNING          0x05
#define WD_MODE_EMERGENCY_PANIC_WARNING     0x06

#define WD_NO_STROBE                        0x00
#define WD_STROBE_IN_PARALLEL               0x01

#define WD_SIREN_LEVEL_LOW_LEVEL            0x00
#define WD_SIREN_LEVEL_MEDIUM_LEVEL         0x01
#define WD_SIREN_LEVEL_HIGH_LEVEL           0x02
#define WD_SIREN_LEVEL_VERY_LEVEL           0x03

#define WD_STROBE_LEVEL_LOW_LEVEL           0x00
#define WD_STROBE_LEVEL_MEDIUM_LEVEL        0x01
#define WD_STROBE_LEVEL_HIGH_LEVEL          0x02
#define WD_STROBE_LEVEL_VERY_LEVEL          0x03

#define WD_SQUAWK_LEVEL_LOW_LEVEL           0x00
#define WD_SQUAWK_LEVEL_MEDIUM_LEVEL        0x01
#define WD_SQUAWK_LEVEL_HIGH_LEVEL          0x02
#define WD_SQUAWK_LEVEL_VERY_LEVEL          0x03

// Event function forward declarations
void emberAfUserAppStartWarningEventHandler(void);
void emberAfUserAppStartWarningTimeoutEventHandler(void);
void emberAfIasWdStopWarning(void);
void emberAfIasWdStartBurglarWarning(int8u sirenlevel,
                                     int16u warningDuration,
                                     int8u strobe,
                                     int8u strobeDutyCycle,
                                     int8u strobeLevel);
void emberAfIasWdStartFireWarning(int8u sirenlevel,
                                  int16u warningDuration,
                                  int8u strobe,
                                  int8u strobeDutyCycle,
                                  int8u strobeLevel);
void emberAfIasWdStartEmergencyWarning(int8u sirenlevel,
                                       int16u warningDuration,
                                       int8u strobe,
                                       int8u strobeDutyCycle,
                                       int8u strobeLevel);
void emberAfIasWdStartPolicePanicWarning(int8u sirenlevel,
                                         int16u warningDuration,
                                         int8u strobe,
                                         int8u strobeDutyCycle,
                                         int8u strobeLevel);
void emberAfIasWdStartFirePanicWarning(int8u sirenlevel,
                                       int16u warningDuration,
                                       int8u strobe,
                                       int8u strobeDutyCycle,
                                       int8u strobeLevel);
void emberAfIasWdStartEmergencyPanicWarning(int8u sirenlevel,
                                            int16u warningDuration,
                                            int8u strobe,
                                            int8u strobeDutyCycle,
                                            int8u strobeLevel);
// Event function stubs
void emberAfUserAppStartWarningEventHandler(void)
{
  emberEventControlSetDelayMS(emberAfUserAppStartWarningEventControl,150);
  halStackIndicatePresence();
  halToggleLed(BOARDLED1);
}

void emberAfUserAppStartWarningTimeoutEventHandler(void)
{
  emberEventControlSetInactive(emberAfUserAppStartWarningTimeoutEventControl);
  emberEventControlSetInactive(emberAfUserAppStartWarningEventControl);
  halClearLed(BOARDLED1);
  halStopTune();
}



void emberAfIasWdStopWarning(void)
{
  emberEventControlSetInactive(emberAfUserAppStartWarningEventControl);
  halClearLed(BOARDLED1);
  halStopTune();
}

void emberAfIasWdStartBurglarWarning(int8u sirenlevel,
                                     int16u warningDuration,
                                     int8u strobe,
                                     int8u strobeDutyCycle,
                                     int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

void emberAfIasWdStartFireWarning(int8u sirenlevel,
                                     int16u warningDuration,
                                     int8u strobe,
                                     int8u strobeDutyCycle,
                                     int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

void emberAfIasWdStartEmergencyWarning(int8u sirenlevel,
                                       int16u warningDuration,
                                       int8u strobe,
                                       int8u strobeDutyCycle,
                                       int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

void emberAfIasWdStartPolicePanicWarning(int8u sirenlevel,
                                     int16u warningDuration,
                                     int8u strobe,
                                     int8u strobeDutyCycle,
                                     int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

void emberAfIasWdStartFirePanicWarning(int8u sirenlevel,
                                     int16u warningDuration,
                                     int8u strobe,
                                     int8u strobeDutyCycle,
                                     int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

void emberAfIasWdStartEmergencyPanicWarning(int8u sirenlevel,
                                            int16u warningDuration,
                                            int8u strobe,
                                            int8u strobeDutyCycle,
                                            int8u strobeLevel)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,
                              warningDuration*MILLISECOND_TICKS_PER_SECOND);
}

/** @brief IAS WD Cluster Start Warning
 *
 *
 *
 * @param warningInfo   Ver.: always
 * @param warningDuration   Ver.: always
 * @param strobeDutyCycle   Ver.: since ha-1.2-05-3520-29
 * @param strobeLevel   Ver.: since ha-1.2-05-3520-29
 */
boolean emberAfIasWdClusterStartWarningCallback(int8u warningInfo,
                                                int16u warningDuration,
                                                int8u strobeDutyCycle,
                                                int8u strobeLevel)
{
  int8u endpoint;
  int16u WarningDuration, MaxDuration;
  EmberAfStatus status = EMBER_ZCL_STATUS_FAILURE;
  endpoint = emberAfCurrentCommand()->apsFrame->destinationEndpoint;

  status = emberAfReadServerAttribute(endpoint,
                                      ZCL_IAS_WD_CLUSTER_ID,
                                      ZCL_MAX_DURATION_ATTRIBUTE_ID,
                                      (int8u*)&MaxDuration,
                                      sizeof(int16u));
  if(status == EMBER_ZCL_STATUS_SUCCESS)
    WarningDuration = (warningDuration > MaxDuration)? MaxDuration : warningDuration;
  else
    WarningDuration = warningDuration;

  WarningInfo_t *pWi = (WarningInfo_t*)&warningInfo;

  switch(pWi->mode)
  {
  case WD_MODE_STOP_WARNING:   /* Stop (no warning) */
    emberAfIasWdStopWarning();
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;
  case WD_MODE_BURGLAR_WARNING: /* Burglar */
    emberAfIasWdStartBurglarWarning(pWi->sirenLevel,
                                    WarningDuration,
                                    pWi->strobe,
                                    strobeDutyCycle,
                                    strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;
  case WD_MODE_FIRE_WARNING: /* Fire */
    emberAfIasWdStartFireWarning(pWi->sirenLevel,
                                 WarningDuration,
                                 pWi->strobe,
                                 strobeDutyCycle,
                                 strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;

  case WD_MODE_EMERGENCY_WARNING: /* Emergency */
    emberAfIasWdStartEmergencyWarning(pWi->sirenLevel,
                                      WarningDuration,
                                      pWi->strobe,
                                      strobeDutyCycle,
                                      strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;

  case WD_MODE_POLICE_PANIC_WARNING:  /* Police panic */
    emberAfIasWdStartPolicePanicWarning(pWi->sirenLevel,
                                        WarningDuration,
                                        pWi->strobe,
                                        strobeDutyCycle,
                                        strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;
  case WD_MODE_FIRE_PANIC_WARNING:   /* Fire panic */
    emberAfIasWdStartFirePanicWarning(pWi->sirenLevel,
                                      WarningDuration,
                                      pWi->strobe,
                                      strobeDutyCycle,
                                      strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;
  case WD_MODE_EMERGENCY_PANIC_WARNING:   /* Emergency Panic */
    emberAfIasWdStartEmergencyPanicWarning(pWi->sirenLevel,
                                           WarningDuration,
                                           pWi->strobe,
                                           strobeDutyCycle,
                                           strobeLevel);
    status = EMBER_ZCL_STATUS_SUCCESS;
    break;
  }
  return status;
}

/** @brief IAS WD Cluster Squawk
 *
 *
 *
 * @param squawkInfo   Ver.: always
 */
boolean emberAfIasWdClusterSquawkCallback(int8u squawkInfo)
{
  emberEventControlSetActive(emberAfUserAppStartWarningEventControl);
  emberEventControlSetDelayMS(emberAfUserAppStartWarningTimeoutEventControl,2*MILLISECOND_TICKS_PER_SECOND);
  return TRUE;
}

/** @brief IAS WD Cluster Server Attribute Changed
 *
 * Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfIasWdClusterServerAttributeChangedCallback(int8u endpoint,
                                                       EmberAfAttributeId attributeId)
{
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
  emberAfPluginConnectionManagerFactoryReset();
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
  emberAfIasWdStopWarning();
}

/** @brief Main Tick
 *
 * Whenever main application tick is called, this callback will be called at the
 * end of the main tick execution.
 *
 */
void emberAfMainTickCallback(void)
{
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

/** @brief Pre Attribute Change
 *
 * This function is called by the application framework before it changes an
 * attribute value.  The value passed into this callback is the value to which
 * the attribute is to be set by the framework.  The application should return
 * ::EMBER_ZCL_STATUS_SUCCESS to permit the change or any other ::EmberAfStatus
 * to reject it.
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
EmberAfStatus emberAfPreAttributeChangeCallback(int8u endpoint,
                                                EmberAfClusterId clusterId,
                                                EmberAfAttributeId attributeId,
                                                int8u mask,
                                                int16u manufacturerCode,
                                                int8u type,
                                                int8u size,
                                                int8u* value)
{
  return EMBER_ZCL_STATUS_SUCCESS;
}

/** @brief Button0 Pressing
 *
 * This function is periodically called when button 0 is being pressed.
 *
 */
void emberAfPluginButtonInterfaceButton0PressingCallback(void)
{
  emberAfPluginConnectionManagerFactoryReset();
  emberAfPluginConnectionManagerLeaveNetworkAndStartSearchForNewOne();
}

/** @brief IAS WD Cluster Server Tick
 *
 * Server Tick
 *
 * @param endpoint Endpoint that is being served  Ver.: always
 */
void emberAfIasWdClusterServerTickCallback(int8u endpoint)
{

}

/** @brief IAS WD Cluster Server Init
 *
 * Server Init
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfIasWdClusterServerInitCallback(int8u endpoint)
{

}

/** @brief IAS WD Cluster Server Pre Attribute Changed
 *
 * Server Pre Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute to be changed  Ver.: always
 * @param attributeType Attribute type  Ver.: always
 * @param size Attribute size  Ver.: always
 * @param value Attribute value  Ver.: always
 */
EmberAfStatus emberAfIasWdClusterServerPreAttributeChangedCallback(int8u endpoint,
                                                                   EmberAfAttributeId attributeId,
                                                                   EmberAfAttributeType attributeType,
                                                                   int8u size,
                                                                   int8u *value)
{
  return EMBER_ZCL_STATUS_SUCCESS;
}


