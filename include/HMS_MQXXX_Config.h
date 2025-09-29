   /*
 ====================================================================================================
 * File:        HMS_MQXXX_Config.h
 * Author:      Hamas Saeed
 * Version:     Rev_1.0.0
 * Date:        Sep 28 2025
 * Brief:       This Package Provide MQXXX Driver Configuration
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

#ifndef HMS_MQXXX_CONFIG_H
#define HMS_MQXXX_CONFIG_H

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:     Enable only if ChronoLog is included                      │
    │ Requires: ChronoLog library → https://github.com/Hamas888/ChronoLog │
    └─────────────────────────────────────────────────────────────────────┘
*/
#define HMS_MQXXX_DEBUG_ENABLED           0                             // Enable debug messages (1=enabled, 0=disabled)


/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Driver selection for MQXXX devices                         │
    │ Support: MQ-2, MQ-135, MQ-131, MQ-303A                              │
    │ Usage:   Uncomment the sensor you want to use as default            │
    └─────────────────────────────────────────────────────────────────────┘
*/
// #define HMS_MQXXX_MQ2                                                   // Define the MQ-2 device to be used
// #define HMS_MQXXX_MQ135                                                 // Define the MQ-135 device to be used
// #define HMS_MQXXX_MQ131                                                 // Define the MQ-131 device to be used
// #define HMS_MQXXX_MQ303A                                                // Define the MQ-303A device to be used


/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Sensor Calibration Constants (a, b coefficients)           │
    │ Usage:   These are the default values used in constructor           │
    │ Source:  Based on typical datasheet values                          │
    └─────────────────────────────────────────────────────────────────────┘
*/
#define HMS_MQXXX_MQ2_A_DEFAULT          574.25f
#define HMS_MQXXX_MQ2_B_DEFAULT          -2.222f
#define HMS_MQXXX_MQ2_REGRESSION         HMS_MQXXX_EXPONENTIAL

// MQ-135 Air Quality Sensor Constants  
#define HMS_MQXXX_MQ135_A_DEFAULT        110.47f
#define HMS_MQXXX_MQ135_B_DEFAULT        -2.862f
#define HMS_MQXXX_MQ135_REGRESSION       HMS_MQXXX_EXPONENTIAL

// MQ-131 Ozone Sensor Constants (Uses inverted ratio R0/Rs)
#define HMS_MQXXX_MQ131_A_DEFAULT        23.943f
#define HMS_MQXXX_MQ131_B_DEFAULT        -1.11f
#define HMS_MQXXX_MQ131_REGRESSION       HMS_MQXXX_EXPONENTIAL

// MQ-303A Alcohol Sensor Constants
#define HMS_MQXXX_MQ303A_A_DEFAULT       4.2f
#define HMS_MQXXX_MQ303A_B_DEFAULT       -1.0f
#define HMS_MQXXX_MQ303A_REGRESSION      HMS_MQXXX_EXPONENTIAL

// Generic/Unknown Sensor Fallback Constants
#define HMS_MQXXX_GENERIC_A_DEFAULT      100.0f
#define HMS_MQXXX_GENERIC_B_DEFAULT      -1.5f
#define HMS_MQXXX_GENERIC_REGRESSION     HMS_MQXXX_EXPONENTIAL

// Auto-select default values based on enabled sensor type
#if defined(HMS_MQXXX_MQ2)
    #define HMS_MQXXX_DEFAULT_A          HMS_MQXXX_MQ2_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B          HMS_MQXXX_MQ2_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_REGRESSION HMS_MQXXX_MQ2_REGRESSION
    #define HMS_MQXXX_DEFAULT_TYPE       HMS_MQXXX_MQ2
#elif defined(HMS_MQXXX_MQ135)
    #define HMS_MQXXX_DEFAULT_A          HMS_MQXXX_MQ135_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B          HMS_MQXXX_MQ135_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_REGRESSION HMS_MQXXX_MQ135_REGRESSION
    #define HMS_MQXXX_DEFAULT_TYPE       HMS_MQXXX_MQ135
#elif defined(HMS_MQXXX_MQ131)
    #define HMS_MQXXX_DEFAULT_A          HMS_MQXXX_MQ131_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B          HMS_MQXXX_MQ131_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_REGRESSION HMS_MQXXX_MQ131_REGRESSION
    #define HMS_MQXXX_DEFAULT_TYPE       HMS_MQXXX_MQ131
#elif defined(HMS_MQXXX_MQ303A)
    #define HMS_MQXXX_DEFAULT_A          HMS_MQXXX_MQ303A_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B          HMS_MQXXX_MQ303A_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_REGRESSION HMS_MQXXX_MQ303A_REGRESSION
    #define HMS_MQXXX_DEFAULT_TYPE       HMS_MQXXX_MQ303A
#else
    // No specific sensor defined, use generic defaults
    #define HMS_MQXXX_DEFAULT_A          HMS_MQXXX_GENERIC_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B          HMS_MQXXX_GENERIC_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_REGRESSION HMS_MQXXX_GENERIC_REGRESSION
    #define HMS_MQXXX_DEFAULT_TYPE       HMS_MQXXX_MQ2
#endif


/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Configuration parameters for MQXXX devices                 │
    └─────────────────────────────────────────────────────────────────────┘
*/
#define HMS_MQXXX_MAX_A                   1e30
#define HMS_MQXXX_MAX_B                   100.0

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Convenience Macros for Quick Access                        │
    │ Usage:   Use these macros to get sensor-specific values             │
    │ Example: float a_value = HMS_MQXXX_GET_A(HMS_MQXXX_MQ2);            │
    └─────────────────────────────────────────────────────────────────────┘
*/
#define HMS_MQXXX_GET_A(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_A_DEFAULT    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_A_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_A_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_A_DEFAULT : \
     HMS_MQXXX_GENERIC_A_DEFAULT)

#define HMS_MQXXX_GET_B(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_B_DEFAULT    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_B_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_B_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_B_DEFAULT : \
     HMS_MQXXX_GENERIC_B_DEFAULT)

#define HMS_MQXXX_GET_REGRESSION(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_REGRESSION    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_REGRESSION  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_REGRESSION  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_REGRESSION : \
     HMS_MQXXX_GENERIC_REGRESSION)


#endif // HMS_MQXXX_CONFIG_H