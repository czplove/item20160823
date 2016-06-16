// *****************************************************************************
// * temperature-measurement-server.c
// *
// * Generic temperature measurement server implementation.  This requires an
// * additional hardware temperature sensor plugin to provide initialization and
// * read functions.
// *
// * Copyright 2015 Silicon Laboratories, Inc.                              *80*
// *****************************************************************************

#ifdef EMBER_SCRIPTED_TEST
#include "app/framework/plugin-soc/temperature-measurement-server/temperature-measurement-server-test.h"
#endif

#include "app/framework/include/af.h"
#include "app/framework/plugin-soc/temperature-measurement-server/temperature-measurement-server.h"
#include EMBER_AF_API_TEMPERATURE

//------------------------------------------------------------------------------
// Plugin private macros

// Shorter macros for plugin options
#define MAX_MEASUREMENT_FREQUENCY_MS \
  (EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_MAX_MEASUREMENT_FREQUENCY_S \
   * MILLISECOND_TICKS_PER_SECOND)

//Macro used to ensure sane temperature max/min values are stored
#define TEMPERATURE_SANITY_CHECK (-30000)
#define HUMIDITY_SANITY_CHECK (0)

//------------------------------------------------------------------------------
// Forward Declaration of private functions
static void writeTemperatureAttributes(int16_t temperatureCentiC);
static void writeHumidityAttributes(uint16_t humidityCentiP);
//------------------------------------------------------------------------------
// Global variables
EmberEventControl emberAfPluginTemperatureMeasurementServerReadEventControl;
static uint32_t temperatureMeasurementRateMS = MAX_MEASUREMENT_FREQUENCY_MS;

//------------------------------------------------------------------------------
// Plugin consumed callback implementations

//******************************************************************************
// Plugin init function
//******************************************************************************
void emberAfPluginTemperatureMeasurementServerInitCallback(void)
{
  // The only initialization needed is to start the ReadEvent, which will
  // re-activate itself perpetually 
  emberEventControlSetActive(
    emberAfPluginTemperatureMeasurementServerReadEventControl);
}

void emberAfPluginTemperatureMeasurementServerStackStatusCallback(
  EmberStatus status)
{
  // On network connect, chances are very good that someone (coordinator,
  // gateway, etc) will poll the temperature for an initial status.  As such,
  // it is useful to have fresh data to be polled.
  if (status == EMBER_NETWORK_UP) {
    emberEventControlSetActive(
      emberAfPluginTemperatureMeasurementServerReadEventControl);
  }
}

//------------------------------------------------------------------------------
// Plugin event handlers

//******************************************************************************
// Event used to generate a read of a new temperature value
//******************************************************************************
void emberAfPluginTemperatureMeasurementServerReadEventHandler(void)
{
  int32_t boardTemperatureMilliC = halTemperatureStartRead();

  emberEventControlSetInactive(
    emberAfPluginTemperatureMeasurementServerReadEventControl);
}

void emberAfPluginTemperatureDataReadyCallback(int16_t temperatureCentiC,
											   uint16_t humidityCentiP,
                                               bool readStatus)
{
  // If the read was successful, post the results to the cluster
  if(readStatus == true) {
    emberAfAppPrintln("Temperature: %d centiC", temperatureCentiC);
    writeTemperatureAttributes(temperatureCentiC);
    emberAfAppPrintln("Humidity: %d centiPercentage", humidityCentiP);
    writeHumidityAttributes(humidityCentiP);
  } else {
    emberAfAppPrintln("Error reading temperature and humidity from HW");
  }
  
  emberEventControlSetDelayMS(
    emberAfPluginTemperatureMeasurementServerReadEventControl,
    temperatureMeasurementRateMS); 
}

//------------------------------------------------------------------------------
// Plugin public functions

void emberAfPluginTemperatureMeasurementServerSetMeasurementRate(
  uint32_t measurementRateS)
{
  if ((measurementRateS == 0)
      || measurementRateS > EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_MAX_MEASUREMENT_FREQUENCY_S) {
    temperatureMeasurementRateMS = MAX_MEASUREMENT_FREQUENCY_MS;
  } else {
    temperatureMeasurementRateMS = measurementRateS * MILLISECOND_TICKS_PER_SECOND;
  }
  emberEventControlSetDelayMS(
    emberAfPluginTemperatureMeasurementServerReadEventControl,
    temperatureMeasurementRateMS); 
}

//------------------------------------------------------------------------------
// Plugin private functions

//******************************************************************************
// Update the temperature attribute of the temperature measurement cluster to
// be the temperature value given by the function's parameter.  This function
// will also query the current max and min read values, and update them if the
// given values is higher (or lower) than the previous records.
//******************************************************************************
static void writeTemperatureAttributes(int16_t temperatureCentiC)
{
  int16_t tempLimitCentiC;
  uint8_t i;
  uint8_t endpoint;

  // Cycle through all endpoints, check to see if the endpoint has a temperature
  // server, and if so update the temperature attributes of that endpoint
  for (i = 0; i < emberAfEndpointCount(); i++) {
    endpoint = emberAfEndpointFromIndex(i);
    if (emberAfContainsServer(endpoint, ZCL_TEMP_MEASUREMENT_CLUSTER_ID)) {
     
      // Write the current temperature attribute
      emberAfWriteServerAttribute(endpoint,
                                  ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                                  ZCL_TEMP_MEASURED_VALUE_ATTRIBUTE_ID,
                                  (uint8_t *) &temperatureCentiC,
                                  ZCL_INT16S_ATTRIBUTE_TYPE);

      // Determine if this is a new minimum measured temperature, and update the
      // TEMP_MIN_MEASURED attribute if that is the case.
      emberAfReadServerAttribute(endpoint,
                                 ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                                 ZCL_TEMP_MIN_MEASURED_VALUE_ATTRIBUTE_ID,
                                 (uint8_t *) (&tempLimitCentiC),
                                 sizeof(int16_t) );
      if ((tempLimitCentiC < TEMPERATURE_SANITY_CHECK)
          || (tempLimitCentiC > temperatureCentiC)) {
        emberAfWriteServerAttribute(endpoint,
                                    ZCL_TEMP_MEASUREMENT_CLUSTER_ID,         
                                    ZCL_TEMP_MIN_MEASURED_VALUE_ATTRIBUTE_ID,
                                    (uint8_t *) &temperatureCentiC,
                                    ZCL_INT16S_ATTRIBUTE_TYPE);              

      }

      // Determine if this is a new maximum measured temperature, and update the
      // TEMP_MAX_MEASURED attribute if that is the case.
      emberAfReadServerAttribute(endpoint,
                                 ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                                 ZCL_TEMP_MAX_MEASURED_VALUE_ATTRIBUTE_ID,
                                 (uint8_t *) (&tempLimitCentiC),
                                 sizeof(int16_t) );
      if ((tempLimitCentiC < TEMPERATURE_SANITY_CHECK)
          || (tempLimitCentiC < temperatureCentiC)) {
        emberAfWriteServerAttribute(endpoint,
                                    ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
                                    ZCL_TEMP_MAX_MEASURED_VALUE_ATTRIBUTE_ID,
                                    (uint8_t *) &temperatureCentiC,
                                    ZCL_INT16S_ATTRIBUTE_TYPE);

      }     
    }
  }
}
//------------------------------------------------------------------------------
// Plugin private functions

//******************************************************************************
// Update the humidity attribute of the humidity measurement cluster to
// be the humidity value given by the function's parameter.  This function
// will also query the current max and min read values, and update them if the
// given values is higher (or lower) than the previous records.
//******************************************************************************
static void writeHumidityAttributes(uint16_t humidityCentiP)
{
  int16_t humLimitCentiP;
  uint8_t i;
  uint8_t endpoint;

  // Cycle through all endpoints, check to see if the endpoint has a humidity
  // server, and if so update the humidity attributes of that endpoint
  for (i = 0; i < emberAfEndpointCount(); i++) {
    endpoint = emberAfEndpointFromIndex(i);
    if (emberAfContainsServer(endpoint, ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID)) {

      // Write the current humidity attribute
      emberAfWriteServerAttribute(endpoint,
                                  ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
                                  ZCL_RELATIVE_HUMIDITY_MEASURED_VALUE_ATTRIBUTE_ID,
                                  (uint8_t *) &humidityCentiP,
                                  ZCL_INT16U_ATTRIBUTE_TYPE);

      // Determine if this is a new minimum measured humidity, and update the
      // TEMP_MIN_MEASURED attribute if that is the case.
      emberAfReadServerAttribute(endpoint,
                                 ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
                                 ZCL_RELATIVE_HUMIDITY_MIN_MEASURED_VALUE_ATTRIBUTE_ID,
                                 (uint8_t *) (&humLimitCentiP),
                                 sizeof(uint16_t) );
      if ((humLimitCentiP < HUMIDITY_SANITY_CHECK)
          || (humLimitCentiP > humidityCentiP)) {
        emberAfWriteServerAttribute(endpoint,
                                    ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
                                    ZCL_RELATIVE_HUMIDITY_MIN_MEASURED_VALUE_ATTRIBUTE_ID,
                                    (uint8_t *) &humidityCentiP,
                                    ZCL_INT16U_ATTRIBUTE_TYPE);

      }

      // Determine if this is a new maximum measured temperature, and update the
      // TEMP_MAX_MEASURED attribute if that is the case.
      emberAfReadServerAttribute(endpoint,
                                 ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
                                 ZCL_RELATIVE_HUMIDITY_MAX_MEASURED_VALUE_ATTRIBUTE_ID,
                                 (uint8_t *) (&humLimitCentiP),
                                 sizeof(uint16_t) );
      if ((humLimitCentiP < HUMIDITY_SANITY_CHECK)
          || (humLimitCentiP < humidityCentiP)) {
        emberAfWriteServerAttribute(endpoint,
                                    ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
                                    ZCL_RELATIVE_HUMIDITY_MAX_MEASURED_VALUE_ATTRIBUTE_ID,
                                    (uint8_t *) &humidityCentiP,
                                    ZCL_INT16U_ATTRIBUTE_TYPE);

      }
    }
  }
}
