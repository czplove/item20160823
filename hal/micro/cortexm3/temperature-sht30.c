// *****************************************************************************
// * temperature-sht30.h
// *
// * API for reading temperature data from an SHT30 temperature sensor
// *
// * It implements the hardware support for a temperature measurement on our
// * production board.  Note:  this can easily be modified to change the
// * ADC value, as well as the curve to translate from ADC voltage to the
// * temperature value.
// *
// * Copyright 2016 Wulian, Inc.                                            *80*
// *****************************************************************************

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "stack/include/event.h"
#include "hal/hal.h"
#include "hal/micro/i2c-driver.h"
#include "hal/micro/micro.h"
#include "hal/micro/temperature.h"

#include "app/framework/include/af.h"

//------------------------------------------------------------------------------
// Plugin private macros

// Si7503 I2C protocol based macros
#define SHT30_I2C_ADDR                    0x88
#define SHT30_I2C_RESET_MSG               0xA230
#define SHT30_I2C_RESET_MSG_LEN           2
#define SHT30_I2C_READ_CFG_MSG            0x0B24
#define SHT30_I2C_READ_CFG_MSG_LEN        2
#define SHT30_SINGLE_MODE_H        		  0x24
#define SHT30_SINGLE_MODE_L               0x0B
#define SHT30_I2C_TEMP_RESPONSE_LEN       6
// This is the maximum amount of time between sending a write command and the
// temperature data being ready.  This is found in table 2 of the data sheet,
// and can be set to a lower value if 11-13 bit conversions are used instead of
// the default 14 bit values.
#define SHT30_I2C_MAX_CONVERSION_TIME_MS  12

//------------------------------------------------------------------------------
// Plugin events
EmberEventControl emberAfPluginTemperatureSht30InitEventControl;
EmberEventControl emberAfPluginTemperatureSht30ReadEventControl;
static uint8_t SHT3X_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum);
static uint8_t SHT3X_CalcCrc(uint8_t data[], uint8_t nbrOfBytes);

//******************************************************************************
// Initialize the sensor
//   Send the reset command over the I2C bus
//   Execute an I2C read for initial temperature value
//******************************************************************************

//------------------------------------------------------------------------------
// Plugin private event handlers

// At this point, I2C driver is guaranteed to have initialized, so it is safe
// to call the i2c based init function
void emberAfPluginTemperatureSht30InitEventHandler(void)
{
  uint16_t resetMsg = SHT30_I2C_RESET_MSG;
  uint8_t resetMsgLen = SHT30_I2C_RESET_MSG_LEN;

  // Send the reset command to the temperature sensor
  halI2cWriteBytes(SHT30_I2C_ADDR, (uint8_t*)&resetMsg, resetMsgLen);

  emberEventControlSetInactive(emberAfPluginTemperatureSht30InitEventControl);
}
void emberAfPluginTemperatureSht30ReadEventHandler(void)
{
  uint8_t status;
  uint8_t tempResponse[SHT30_I2C_TEMP_RESPONSE_LEN];

  int16_t tempMilliDegreesC;
  uint16_t HumidityValue;
  int16_t rawTemperature;
  uint16_t rawHumidity;

  emberEventControlSetInactive(emberAfPluginTemperatureSht30ReadEventControl);

//  // perform the I2C read to get a new data value
  status  = halI2cReadBytes(SHT30_I2C_ADDR,
                            tempResponse,
                            SHT30_I2C_TEMP_RESPONSE_LEN);

  // Verify the read was successful
  if (status) {
    emberAfPluginTemperatureDataReadyCallback(0,0, false);
  }

  if((SHT3X_CheckCrc(&tempResponse[0], 2, tempResponse[2])!=1)&&(SHT3X_CheckCrc(&tempResponse[3], 2, tempResponse[5])!=1))
  {
    rawTemperature = (uint16_t)((tempResponse[0]<<8)|tempResponse[1]);
    tempMilliDegreesC = (int32_t)((17500*rawTemperature)/65535.0-4500);

    rawHumidity = (uint16_t)((tempResponse[3]<<8)|tempResponse[4]);
    HumidityValue = (uint32_t)((10000*rawHumidity)/65535.0);
  }
  else
  {
    emberAfPluginTemperatureDataReadyCallback(0,0,false);
    return;
  }

  emberAfPluginTemperatureDataReadyCallback(tempMilliDegreesC,HumidityValue, true);
}


//------------------------------------------------------------------------------
// Plugin defined callbacks

// The init callback, which will be called by the framework on init.
void emberAfPluginTemperatureSht30InitCallback(void)
{
  halTemperatureInit();
}

//------------------------------------------------------------------------------
// Plugin public functions

// All init functionality requires the I2C plugin to be initialized, which is
// not guaranteed to be the case by the time this function executes.  As a
// result, I2C based init functionality needs to execute from task context.
void halTemperatureInit(void)
{
  emberEventControlSetActive(emberAfPluginTemperatureSht30InitEventControl);

}

//******************************************************************************
// Perform all I2C transactions necessary to read the temperature from the
// SHT30, convert it to milliDegrees Celsius, and return it.
//******************************************************************************
uint8_t halTemperatureStartRead(void)
{
  uint16_t cfgMsg = SHT30_I2C_READ_CFG_MSG;
  uint8_t cfgMsgLen = SHT30_I2C_READ_CFG_MSG_LEN;
  uint8_t status;

  // Write the configuration message to the I2C device to set it to single temp
  // measurement with no hold master, then perform an i2c  read of the
  // temperature register
  status = halI2cWriteBytes(SHT30_I2C_ADDR, (uint8_t*)&cfgMsg, cfgMsgLen);
  if (status) {
    // If the write fails, the device is in a bad state
    return status;
  }

  // It will take a maximum of SHT30_I2C_MAX_CONVERSION_TIME_MS milliseconds
  // for the sensor to finish generating a new value.  Delay that amount of time
  // to ensure that we're not burning power waiting for the generation to finish
  emberEventControlSetDelayMS(emberAfPluginTemperatureSht30ReadEventControl,
                              SHT30_I2C_MAX_CONVERSION_TIME_MS);

  return status;
}


/**
  * @fun    uint8 SHT3X_CalcCrc
  * @brief  CRC Vrify
  * @author huangzibo
  * @param  uint8 data[]
  * @param  uint8 nbrOfBytes
  *
  * @retval
  */
uint8_t SHT3X_CalcCrc(uint8_t data[], uint8_t nbrOfBytes)
{
  uint8_t bit;        // bit mask
  uint8_t crc = 0xFF; // calculated checksum
  uint8_t byteCtr;    // byte counter

  // calculates 8-Bit checksum with given polynomial
  for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++)
  {
    crc ^= (data[byteCtr]);
    for(bit = 8; bit > 0; --bit)
    {
      if(crc & 0x80)
        crc = (crc << 1) ^ 0x131;
      else
        crc = (crc << 1);
    }
  }

  return crc;
}


/**
  * @fun    uint8 SHT3X_CheckCrc
  * @brief  Checkout CRC
  * @author huangzibo
  * @param  uint8 data[]
  * @param  uint8 nbrOfBytes
  * @param  uint8 checksum
  *
  * @retval
  */
uint8_t SHT3X_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum)
{
  uint8_t crc;     // calculated checksum

  // calculates 8-Bit checksum
  crc = SHT3X_CalcCrc(data, nbrOfBytes);

  // verify checksum
  if(crc != checksum) return 1;//ÓÐ´íÎó
  else                return 0;//Ã»´íÎó
}