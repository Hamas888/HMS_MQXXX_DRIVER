/*
    ====================================================================================================
    * File:        HMS_MQXXX_DRIVER.h
    * Author:      Hamas Saeed
    * Version:     Rev_1.0.0
    * Date:        Sep 28 2025
    * Brief:       This Package Provide MQXXX Driver Library for Cross Platform (STM/ESP/nRF)
    * 
    ====================================================================================================
    * License: 
    * MIT License
    * 
    * Copyright (c) 2025 Hamas Saeed
    * 
    * Permission is hereby granted, free of charge, to any person obtaining a copy
    * of this software and associated documentation files (the "Software"), to deal
    * in the Software without restriction, including without limitation the rights
    * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    * copies of the Software, and to permit persons to whom the Software is
    * furnished to do so, subject to the following conditions:
    * 
    * The above copyright notice and this permission notice shall be included in all
    * copies or substantial portions of the Software.
    * 
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    * SOFTWARE.
    * 
    * For any inquiries, contact Hamas Saeed at hamasaeed@gmail.com
    *
    ====================================================================================================
 */


 #ifndef HMS_MQXXX_DRIVER_H
 #define HMS_MQXXX_DRIVER_H

#if defined(ARDUINO)                                                                                       // Platform detection
  #define HMS_MQXXX_PLATFORM_ARDUINO
#elif defined(ESP_PLATFORM)
  #define HMS_MQXXX_PLATFORM_ESP_IDF
#elif defined(__ZEPHYR__)
  #define HMS_MQXXX_PLATFORM_ZEPHYR
#elif defined( __STM32__)
  #define HMS_MQXXX_PLATFORM_STM32_HAL
#endif

#if defined(HMS_MQXXX_PLATFORM_ARDUINO)
  #include <Arduino.h>
  #include <stdint.h>
  #include <float.h>
  #include <math.h>
#elif defined(HMS_MQXXX_PLATFORM_ESP_IDF)
#elif defined(HMS_MQXXX_PLATFORM_ZEPHYR)
  #include <stdio.h>
  #include <zephyr/device.h>
  #include <zephyr/drivers/i2c.h>
#elif defined(HMS_MQXXX_PLATFORM_STM32_HAL)
  #include "main.h"
  #include <stdio.h>
#endif

#endif // HMS_MQXXX_DRIVER_H

#include "HMS_MQXXX_Config.h"

#if defined(HMS_MQXXX_DEBUG_ENABLED) && (HMS_MQXXX_DEBUG_ENABLED == 1)
  #define HMS_MQXXX_LOGGER_ENABLED
#endif

typedef enum {
    HMS_MQXXX_MQ2,
    HMS_MQXXX_MQ135
} HMS_MQXXX_Type;

typedef enum {
    HMS_MQXXX_OK       = 0x00,
    HMS_MQXXX_ERROR    = 0x01,
    HMS_MQXXX_NOT_FOUND= 0x04
} HMS_MQXXX_StatusTypeDef;

typedef enum {
    HMS_MQXXX_LINEAR      = 2,
    HMS_MQXXX_EXPONENTIAL = 1
} HMS_MQXXX_RegressionMethod;

class HMS_MQXXX {
    public:
        #if defined(HMS_MQXXX_PLATFORM_STM32_HAL)
            HMS_MQXXX(GPIO_TypeDef *port, uint32_t pin, HMS_MQXXX_Type = HMS_MQXXX_MQ2);
        #endif

        //Functions to set values
        HMS_MQXXX_StatusTypeDef init();
        HMS_MQXXX_StatusTypeDef update();
        // void externalADCUpdate(float volt);
        // void setR0(float R0 = 10);
        // void setRL(float RL = 10);
        // void setA(float a);
        // void setB(float b);
        // void setRegressionMethod(int regressionMethod);
        // void setVoltResolution(float voltage_resolution =  5);
        // void setVCC(float vcc = 5);
        // void setPin(int pin = 1);
        // void serialDebug(bool onSetup = false); //Show on serial port information about sensor
        // void setADC(int value); //For external ADC Usage
    
        //user functions
        // float calibrate(float ratioInCleanAir, float correctionFactor = 0.0);
        // float readSensor(bool isMQ303A = false, float correctionFactor = 0.0, bool injected=false);
        // float readSensorR0Rs(float correctionFactor = 0.0);
        // float validateEcuation(float ratioInput = 0);
    
        //get function for info
        float getA() const                                      { return a;                }
        float getB() const                                      { return b;                }
        float getR0() const                                     { return r0;               }
        float getRL() const                                     { return rl;               }
        float getADC() const                                    { return adc;              }
        HMS_MQXXX_Type getType() const                          { return type;             }

        HMS_MQXXX_RegressionMethod getRegressionMethod() const  { return regressionMethod; }

        // float getVoltResolution();
        // float getVCC();
        // String getRegressionMethod();
        // float getVoltage(bool read = true, bool injected = false, int value = 0);
        // float stringTofloat(String & str);

        // functions for testing
        float getRS();    
        float setRsR0RatioGetPPM(float value);

    private:
        #if defined(HMS_MQXXX_PLATFORM_ARDUINO)
            float           voltageResolution   = 5.0;  
            uint8_t         adcBitResolution    = 10;
            uint8_t         pin                 = A0;
        #elif defined(HMS_MQXXX_PLATFORM_ZEPHYR)
            float           voltageResolution   = 3.3;
            uint8_t         adcBitResolution    = 12;
            const struct device *adc_dev        = NULL;
            uint8_t         pin                 = 0;
            uint8_t         channel             = 0;
            int16_t         adc_raw             = 0;
            int             ret                 = 0;
        #elif defined(HMS_MQXXX_PLATFORM_ESP_IDF)
            float           voltageResolution   = 3.3;
            uint8_t         adcBitResolution    = 10;
            uint8_t         pin                 = 36;
        #elif defined(HMS_MQXXX_PLATFORM_STM32_HAL)
            float           voltageResolution   = 3.3;  
            uint8_t         adcBitResolution    = 12;
            uint32_t        pin                 = 0;
            GPIO_TypeDef    *port               = NULL;
        #endif

        bool                       firstFlag = false;                           // Flag for first initialization
        float                       vcc = 5.0;                                  // Sensor supply voltage
        float                       rl = 10;                                    // Load resistance in kilo ohms
        float                       a;                                          // Coefficient a for the equation
        float                       b;                                          // Coefficient b for the equation
        float                       adc;                                        // Raw ADC value
        float                       r0;                                         // Sensor resistance in clean air
        float                       ppm;                                        // Calculated ppm value
        float                       rsAir;                                      // Sensor resistance in clean air
        float                       ratio;                                      // Rs/R0 ratio
        float                       rsCalc;                                     // Calculated sensor resistance
        float                       sensorVolt;                                 // Sensor voltage
        HMS_MQXXX_Type              type;                                       // Sensor type
        HMS_MQXXX_RegressionMethod  regressionMethod;                           // Regression method
};

#endif // HMS_MQXXX_DRIVER_H