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
 * Understanding MIN/MAX Values in HMS_MQXXX Configuration
 * 
 * This file explains what the MIN and MAX values represent and why they're important.
 * 
 * Author: Hamas Saeed
 * Date: Sep 30, 2025
 */

/*
 * ╔═══════════════════════════════════════════════════════════════════════════════════╗
 * ║                          WHAT ARE MIN/MAX VALUES?                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════╝
 * 
 * MIN/MAX values represent the DETECTION RANGE of each sensor for specific gases.
 * These are the lowest and highest concentrations the sensor can reliably measure.
 * 
 * Example: HMS_MQXXX_MQ2_MIN_LPG = 300.0f, HMS_MQXXX_MQ2_MAX_LPG = 10000.0f
 * 
 * This means:
 * - MQ-2 can detect LPG from 300 ppm to 10,000 ppm
 * - Below 300 ppm: Sensor may not respond or give unreliable readings
 * - Above 10,000 ppm: Sensor may saturate or give inaccurate readings
 */

/*
 * ╔═══════════════════════════════════════════════════════════════════════════════════╗
 * ║                            DATASHEET VALUES                                       ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════╝
 * 
 * ┌───────────────────────────────────────────────────────────────────────────────────┐
 * │ MQ-2 Smoke/Combustible Gas Sensor                                                 │
 * ├───────────────────────────────────────────────────────────────────────────────────┤
 * │ Gas      │ Min PPM │ Max PPM  │ Real-World Examples                               │
 * │──────────│─────────│──────────│───────────────────────────────────────────────────│
 * │ LPG      │ 300     │ 10,000   │ Gas leak detection (dangerous >1000 ppm)          │
 * │ Propane  │ 300     │ 5,000    │ BBQ gas, camping fuel                             │
 * │ Hydrogen │ 300     │ 5,000    │ Industrial gas, fuel cells                        │
 * │ Alcohol  │ 100     │ 2,000    │ Breath alcohol, industrial solvents               │
 * │ CO       │ 20      │ 2,000    │ Car exhaust, incomplete combustion (toxic >50ppm) │
 * └───────────────────────────────────────────────────────────────────────────────────┘
 * 
 * ┌───────────────────────────────────────────────────────────────────────────────────┐
 * │ MQ-135 Air Quality Sensor                                                         │
 * ├───────────────────────────────────────────────────────────────────────────────────┤
 * │ Gas      │ Min PPM │ Max PPM  │ Real-World Examples                               │
 * │──────────│─────────│──────────│───────────────────────────────────────────────────│
 * │ CO2      │ 10      │ 10,000   │ Outdoor:400, Indoor:600-1000, Poor:>1000          │
 * │ NH3      │ 1       │ 500      │ Cleaning products, fertilizers                    │
 * │ Alcohol  │ 1       │ 500      │ Sanitizers, industrial cleaning                   │
 * │ Toluene  │ 1       │ 1,000    │ Paint thinners, adhesives                         │
 * │ Acetone  │ 1       │ 1,000    │ Nail polish remover, paint                        │
 * │ CO       │ 1       │ 1,000    │ Same as MQ-2 but different sensitivity            │
 * └───────────────────────────────────────────────────────────────────────────────────┘
 * 
 * ┌───────────────────────────────────────────────────────────────────────────────────┐
 * │ MQ-131 Ozone Sensor (High Precision)                                              │
 * ├───────────────────────────────────────────────────────────────────────────────────┤
 * │ Gas      │ Min PPM │ Max PPM  │ Real-World Examples                               │
 * │──────────│─────────│──────────│───────────────────────────────────────────────────│
 * │ O3       │ 0.01    │ 2.0      │ Outdoor:0.02-0.1, Smog:0.2+, Dangerous:>0.5       │
 * │ NO2      │ 0.05    │ 10.0     │ Traffic pollution, industrial emissions           │
 * │ Cl2      │ 0.1     │ 20.0     │ Swimming pools, water treatment                   │
 * └───────────────────────────────────────────────────────────────────────────────────┘
 * 
 * ┌───────────────────────────────────────────────────────────────────────────────────┐
 * │ MQ-303A Alcohol Sensor (Breath/Industrial)                                        │
 * ├───────────────────────────────────────────────────────────────────────────────────┤
 * │ Gas         │ Min PPM │ Max PPM  │ Real-World Examples                            │
 * │─────────────│─────────│──────────│────────────────────────────────────────────────│
 * │ Ethanol     │ 25      │ 500      │ Breath:25-100, Drunk:100+, Industrial solvents │
 * │ Hydrogen    │ 1       │ 1,000    │ Fuel cells, industrial processes               │
 * │ Iso-butane  │ 1       │ 1,000    │ Lighter fluid, aerosol propellant              │
 * └───────────────────────────────────────────────────────────────────────────────────┘
 */

/*
 * ╔═══════════════════════════════════════════════════════════════════════════════════╗
 * ║                              WHY THESE VALUES MATTER                              ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════╝
 * 
 * 1. SAFETY APPLICATIONS:
 *    - Gas leak detection: Need to detect dangerous levels
 *    - Air quality monitoring: Health-based thresholds
 *    - Industrial safety: OSHA/regulatory compliance
 * 
 * 2. VALIDATION:
 *    - Ensures readings are within sensor capability
 *    - Prevents false alarms from out-of-range values
 *    - Helps determine sensor accuracy
 * 
 * 3. APPLICATION SELECTION:
 *    - Choose right sensor for your detection needs
 *    - Avoid using sensor outside its range
 *    - Optimize sensitivity for specific applications
 */

/*
 * ╔════════════════════════════════════════════════════════════════════════════════════╗
 * ║                               SAFETY THRESHOLDS                                    ║
 * ╚════════════════════════════════════════════════════════════════════════════════════╝
 * 
 * Common Safety Levels (for reference):
 * 
 * CO (Carbon Monoxide):
 *   - 0-9 ppm: Normal outdoor levels
 *   - 10-20 ppm: Elevated, investigate source
 *   - 30-50 ppm: Dangerous, ventilate immediately
 *   - 50+ ppm: Evacuate, life threatening
 * 
 * LPG (Propane/Butane):
 *   - 0-500 ppm: Normal levels
 *   - 500-1000 ppm: Investigate potential leak
 *   - 1000+ ppm: Dangerous, potential explosion risk
 * 
 * CO2 (Carbon Dioxide):
 *   - 400 ppm: Normal outdoor air
 *   - 600-800 ppm: Acceptable indoor levels
 *   - 1000+ ppm: Poor ventilation, drowsiness
 *   - 5000+ ppm: Workplace exposure limit
 * 
 * O3 (Ozone):
 *   - 0.02-0.05 ppm: Normal levels
 *   - 0.1 ppm: Unhealthy for sensitive people
 *   - 0.2+ ppm: Unhealthy for everyone
 */


/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Sensor Calibration Constants (a, b coefficients)           │
    │ Usage:   These are the default values used in constructor           │
    │ Source:  Based on typical datasheet values and curve fitting        │
    │ Format:  Each sensor has multiple gas-specific constants            │
    └─────────────────────────────────────────────────────────────────────┘
*/

// MQ-2 Gas Sensor Constants
#define HMS_MQXXX_MQ2_A_H2                  987.99f
#define HMS_MQXXX_MQ2_B_H2                  -2.162f
#define HMS_MQXXX_MQ2_MIN_H2                300.0f
#define HMS_MQXXX_MQ2_MAX_H2                5000.0f

#define HMS_MQXXX_MQ2_A_CO                  36974.0f
#define HMS_MQXXX_MQ2_B_CO                  -3.109f
#define HMS_MQXXX_MQ2_MIN_CO                20.0f
#define HMS_MQXXX_MQ2_MAX_CO                2000.0f

#define HMS_MQXXX_MQ2_A_LPG                 574.25f
#define HMS_MQXXX_MQ2_B_LPG                 -2.222f
#define HMS_MQXXX_MQ2_MIN_LPG               300.0f
#define HMS_MQXXX_MQ2_MAX_LPG               10000.0f

#define HMS_MQXXX_MQ2_A_ALCOHOL             3616.1f
#define HMS_MQXXX_MQ2_B_ALCOHOL             -2.675f
#define HMS_MQXXX_MQ2_MIN_ALCOHOL           100.0f
#define HMS_MQXXX_MQ2_MAX_ALCOHOL           2000.0f

#define HMS_MQXXX_MQ2_A_PROPANE             658.71f
#define HMS_MQXXX_MQ2_B_PROPANE             -2.168f
#define HMS_MQXXX_MQ2_MIN_PROPANE           300.0f
#define HMS_MQXXX_MQ2_MAX_PROPANE           5000.0f

// MQ-2 Default Gas (LPG) and Settings
#define HMS_MQXXX_MQ2_A_DEFAULT             HMS_MQXXX_MQ2_A_LPG
#define HMS_MQXXX_MQ2_B_DEFAULT             HMS_MQXXX_MQ2_B_LPG
#define HMS_MQXXX_MQ2_MIN_DEFAULT           HMS_MQXXX_MQ2_MIN_LPG
#define HMS_MQXXX_MQ2_MAX_DEFAULT           HMS_MQXXX_MQ2_MAX_LPG
#define HMS_MQXXX_MQ2_REGRESSION            HMS_MQXXX_EXPONENTIAL
#define HMS_MQXXX_MQ2_CLEAN_AIR_RATIO       9.83f                    // Rs/R0 ratio in clean air

// MQ-135 Air Quality Sensor Constants
#define HMS_MQXXX_MQ135_A_CO                605.18f
#define HMS_MQXXX_MQ135_B_CO                -3.937f
#define HMS_MQXXX_MQ135_MIN_CO              1.0f
#define HMS_MQXXX_MQ135_MAX_CO              1000.0f

#define HMS_MQXXX_MQ135_A_CO2               110.47f
#define HMS_MQXXX_MQ135_B_CO2               -2.862f
#define HMS_MQXXX_MQ135_MIN_CO2             10.0f
#define HMS_MQXXX_MQ135_MAX_CO2             10000.0f

#define HMS_MQXXX_MQ135_A_NH3               102.2f
#define HMS_MQXXX_MQ135_B_NH3               -2.473f
#define HMS_MQXXX_MQ135_MIN_NH3             1.0f
#define HMS_MQXXX_MQ135_MAX_NH3             500.0f

#define HMS_MQXXX_MQ135_A_TOLUENE           44.947f
#define HMS_MQXXX_MQ135_B_TOLUENE           -3.445f
#define HMS_MQXXX_MQ135_MIN_TOLUENE         1.0f
#define HMS_MQXXX_MQ135_MAX_TOLUENE         1000.0f

#define HMS_MQXXX_MQ135_A_ACETONE           34.668f
#define HMS_MQXXX_MQ135_B_ACETONE           -3.369f
#define HMS_MQXXX_MQ135_MIN_ACETONE         1.0f
#define HMS_MQXXX_MQ135_MAX_ACETONE         1000.0f

#define HMS_MQXXX_MQ135_A_ALCOHOL           77.255f
#define HMS_MQXXX_MQ135_B_ALCOHOL           -3.18f
#define HMS_MQXXX_MQ135_MIN_ALCOHOL         1.0f
#define HMS_MQXXX_MQ135_MAX_ALCOHOL         500.0f

// MQ-135 Default Gas (CO2) and Settings
#define HMS_MQXXX_MQ135_A_DEFAULT           HMS_MQXXX_MQ135_A_CO2
#define HMS_MQXXX_MQ135_B_DEFAULT           HMS_MQXXX_MQ135_B_CO2
#define HMS_MQXXX_MQ135_MIN_DEFAULT         HMS_MQXXX_MQ135_MIN_CO2
#define HMS_MQXXX_MQ135_MAX_DEFAULT         HMS_MQXXX_MQ135_MAX_CO2
#define HMS_MQXXX_MQ135_REGRESSION          HMS_MQXXX_EXPONENTIAL
#define HMS_MQXXX_MQ135_CLEAN_AIR_RATIO     3.6f                     // Rs/R0 ratio in clean air

// MQ-131 Ozone Sensor Constants
#define HMS_MQXXX_MQ131_A_O3                23.943f
#define HMS_MQXXX_MQ131_B_O3                -1.11f
#define HMS_MQXXX_MQ131_MIN_O3              0.01f 
#define HMS_MQXXX_MQ131_MAX_O3              2.0f

#define HMS_MQXXX_MQ131_A_NO2               -462.43f
#define HMS_MQXXX_MQ131_B_NO2               -2.204f
#define HMS_MQXXX_MQ131_MIN_NO2             0.05f
#define HMS_MQXXX_MQ131_MAX_NO2             10.0f

#define HMS_MQXXX_MQ131_A_CL2               47.209f
#define HMS_MQXXX_MQ131_B_CL2               -1.186f
#define HMS_MQXXX_MQ131_MIN_CL2             0.1f
#define HMS_MQXXX_MQ131_MAX_CL2             20.0f

// MQ-131 Default Gas (O3) and Settings
#define HMS_MQXXX_MQ131_A_DEFAULT           HMS_MQXXX_MQ131_A_O3
#define HMS_MQXXX_MQ131_B_DEFAULT           HMS_MQXXX_MQ131_B_O3
#define HMS_MQXXX_MQ131_MIN_DEFAULT         HMS_MQXXX_MQ131_MIN_O3
#define HMS_MQXXX_MQ131_MAX_DEFAULT         HMS_MQXXX_MQ131_MAX_O3
#define HMS_MQXXX_MQ131_REGRESSION          HMS_MQXXX_EXPONENTIAL
#define HMS_MQXXX_MQ131_CLEAN_AIR_RATIO     15.0f                    // R0/Rs ratio in clean air

// MQ-303A Alcohol Sensor Constants
#define HMS_MQXXX_MQ303A_A_ETHANOL          3.4916f
#define HMS_MQXXX_MQ303A_B_ETHANOL          -2.432f
#define HMS_MQXXX_MQ303A_MIN_ETHANOL        25.0f
#define HMS_MQXXX_MQ303A_MAX_ETHANOL        500.0f

#define HMS_MQXXX_MQ303A_A_HYDROGEN         4.1487f
#define HMS_MQXXX_MQ303A_B_HYDROGEN         -2.716f
#define HMS_MQXXX_MQ303A_MIN_HYDROGEN       1.0f
#define HMS_MQXXX_MQ303A_MAX_HYDROGEN       1000.0f

#define HMS_MQXXX_MQ303A_A_ISO_BUTANE       6.2144f
#define HMS_MQXXX_MQ303A_B_ISO_BUTANE       -2.894f
#define HMS_MQXXX_MQ303A_MIN_ISO_BUTANE     1.0f
#define HMS_MQXXX_MQ303A_MAX_ISO_BUTANE     1000.0f

// MQ-303A Default Gas (Ethanol) and Settings
#define HMS_MQXXX_MQ303A_A_DEFAULT          HMS_MQXXX_MQ303A_A_ETHANOL
#define HMS_MQXXX_MQ303A_B_DEFAULT          HMS_MQXXX_MQ303A_B_ETHANOL
#define HMS_MQXXX_MQ303A_MIN_DEFAULT        HMS_MQXXX_MQ303A_MIN_ETHANOL
#define HMS_MQXXX_MQ303A_MAX_DEFAULT        HMS_MQXXX_MQ303A_MAX_ETHANOL
#define HMS_MQXXX_MQ303A_REGRESSION         HMS_MQXXX_EXPONENTIAL
#define HMS_MQXXX_MQ303A_CLEAN_AIR_RATIO    1.0f                     // Rs/R0 ratio in clean air

// Generic/Unknown Sensor Fallback Constants
#define HMS_MQXXX_GENERIC_A_DEFAULT         HMS_MQXXX_MQ135_A_DEFAULT
#define HMS_MQXXX_GENERIC_B_DEFAULT         HMS_MQXXX_MQ135_B_DEFAULT
#define HMS_MQXXX_GENERIC_MIN_DEFAULT       HMS_MQXXX_MQ135_MIN_DEFAULT
#define HMS_MQXXX_GENERIC_MAX_DEFAULT       HMS_MQXXX_MQ135_MAX_DEFAULT
#define HMS_MQXXX_GENERIC_REGRESSION        HMS_MQXXX_MQ135_REGRESSION
#define HMS_MQXXX_GENERIC_CLEAN_AIR_RATIO   HMS_MQXXX_MQ135_CLEAN_AIR_RATIO

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Heater Configuration (Optional - Advanced Users)           │
    │ Usage:   Heater voltage and preheat times for accurate readings     │
    │ Info:    Most MQ sensors need 24-48h burn-in, 2-5min preheat        │
    └─────────────────────────────────────────────────────────────────────┘
*/

// MQ-2 Heater Settings
#define HMS_MQXXX_MQ2_HEATER_VOLTAGE        5.0f                     // Heater voltage (V)
#define HMS_MQXXX_MQ2_PREHEAT_TIME          180                      // Preheat time (seconds)
#define HMS_MQXXX_MQ2_BURN_IN_TIME          24                       // Burn-in time (hours)

// MQ-135 Heater Settings  
#define HMS_MQXXX_MQ135_HEATER_VOLTAGE      5.0f                     // Heater voltage (V)
#define HMS_MQXXX_MQ135_PREHEAT_TIME        180                      // Preheat time (seconds)
#define HMS_MQXXX_MQ135_BURN_IN_TIME        24                       // Burn-in time (hours)

// MQ-131 Heater Settings
#define HMS_MQXXX_MQ131_HEATER_VOLTAGE      6.0f                     // Heater voltage (V) - Higher for O3
#define HMS_MQXXX_MQ131_PREHEAT_TIME        300                      // Preheat time (seconds) - Longer for precision
#define HMS_MQXXX_MQ131_BURN_IN_TIME        48                       // Burn-in time (hours) - Longer for stability

// MQ-303A Heater Settings
#define HMS_MQXXX_MQ303A_HEATER_VOLTAGE     5.0f                     // Heater voltage (V)
#define HMS_MQXXX_MQ303A_PREHEAT_TIME       120                      // Preheat time (seconds) - Faster for alcohol
#define HMS_MQXXX_MQ303A_BURN_IN_TIME       24                       // Burn-in time (hours)

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Temperature & Humidity Compensation (Optional)             │
    │ Usage:   Correction factors for environmental conditions            │
    │ Formula: corrected_ppm = raw_ppm * temp_factor * humidity_factor    │
    │ Info:    Most MQ sensors are affected by temperature and humidity   │
    └─────────────────────────────────────────────────────────────────────┘
*/

// Temperature Compensation (20°C baseline)
#define HMS_MQXXX_TEMP_BASELINE             20.0f                    // Reference temperature (°C)
#define HMS_MQXXX_TEMP_COEFF_GENERIC        0.004f                   // Generic temp coefficient (%/°C)
#define HMS_CALIBRATIION_SAMPLES            5

// MQ sensor-specific temperature coefficients
#define HMS_MQXXX_MQ2_TEMP_COEFF            0.005f                   // Temperature coefficient (%/°C)
#define HMS_MQXXX_MQ135_TEMP_COEFF          0.004f                   // Temperature coefficient (%/°C)  
#define HMS_MQXXX_MQ131_TEMP_COEFF          0.003f                   // Temperature coefficient (%/°C) - More stable
#define HMS_MQXXX_MQ303A_TEMP_COEFF         0.006f                   // Temperature coefficient (%/°C) - More sensitive

// Humidity Compensation (60% RH baseline)
#define HMS_MQXXX_HUMIDITY_BASELINE         60.0f                    // Reference humidity (%RH)
#define HMS_MQXXX_HUMIDITY_COEFF_GENERIC    0.002f                   // Generic humidity coefficient (%/%RH)

// MQ sensor-specific humidity coefficients  
#define HMS_MQXXX_MQ2_HUMIDITY_COEFF        0.0015f                  // Humidity coefficient (%/%RH)
#define HMS_MQXXX_MQ135_HUMIDITY_COEFF      0.0025f                  // Humidity coefficient (%/%RH) - More affected
#define HMS_MQXXX_MQ131_HUMIDITY_COEFF      0.001f                   // Humidity coefficient (%/%RH) - Less affected
#define HMS_MQXXX_MQ303A_HUMIDITY_COEFF     0.003f                   // Humidity coefficient (%/%RH) - Most affected

// Simple compensation enable/disable (for easy on/off)
#define HMS_MQXXX_ENABLE_ecTEMP_COMPENSATION  0                        // 1=enabled, 0=disabled
#define HMS_MQXXX_ENABLE_HUMIDITY_COMPENSATION 0                     // 1=enabled, 0=disabled

// Auto-select default values based on enabled sensor type
#if defined(HMS_MQXXX_MQ2)
    #define HMS_MQXXX_DEFAULT_A                 HMS_MQXXX_MQ2_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B                 HMS_MQXXX_MQ2_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_MIN               HMS_MQXXX_MQ2_MIN_DEFAULT
    #define HMS_MQXXX_DEFAULT_MAX               HMS_MQXXX_MQ2_MAX_DEFAULT
    #define HMS_MQXXX_DEFAULT_TYPE              HMS_MQXXX_MQ2
    #define HMS_MQXXX_DEFAULT_REGRESSION        HMS_MQXXX_MQ2_REGRESSION
    #define HMS_MQXXX_DEFAULT_CLEAN_AIR_RATIO   HMS_MQXXX_MQ2_CLEAN_AIR_RATIO
#elif defined(HMS_MQXXX_MQ135)
    #define HMS_MQXXX_DEFAULT_A                 HMS_MQXXX_MQ135_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B                 HMS_MQXXX_MQ135_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_MIN               HMS_MQXXX_MQ135_MIN_DEFAULT
    #define HMS_MQXXX_DEFAULT_MAX               HMS_MQXXX_MQ135_MAX_DEFAULT
    #define HMS_MQXXX_DEFAULT_TYPE              HMS_MQXXX_MQ135
    #define HMS_MQXXX_DEFAULT_REGRESSION        HMS_MQXXX_MQ135_REGRESSION
    #define HMS_MQXXX_DEFAULT_CLEAN_AIR_RATIO   HMS_MQXXX_MQ135_CLEAN_AIR_RATIO
#elif defined(HMS_MQXXX_MQ131)
    #define HMS_MQXXX_DEFAULT_A                 HMS_MQXXX_MQ131_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B                 HMS_MQXXX_MQ131_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_MIN               HMS_MQXXX_MQ131_MIN_DEFAULT
    #define HMS_MQXXX_DEFAULT_MAX               HMS_MQXXX_MQ131_MAX_DEFAULT
    #define HMS_MQXXX_DEFAULT_TYPE              HMS_MQXXX_MQ131
    #define HMS_MQXXX_DEFAULT_REGRESSION        HMS_MQXXX_MQ131_REGRESSION
    #define HMS_MQXXX_DEFAULT_CLEAN_AIR_RATIO   HMS_MQXXX_MQ131_CLEAN_AIR_RATIO
#elif defined(HMS_MQXXX_MQ303A)
    #define HMS_MQXXX_DEFAULT_A                 HMS_MQXXX_MQ303A_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B                 HMS_MQXXX_MQ303A_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_MIN               HMS_MQXXX_MQ303A_MIN_DEFAULT
    #define HMS_MQXXX_DEFAULT_MAX               HMS_MQXXX_MQ303A_MAX_DEFAULT
    #define HMS_MQXXX_DEFAULT_TYPE              HMS_MQXXX_MQ303A
    #define HMS_MQXXX_DEFAULT_REGRESSION        HMS_MQXXX_MQ303A_REGRESSION
    #define HMS_MQXXX_DEFAULT_CLEAN_AIR_RATIO   HMS_MQXXX_MQ303A_CLEAN_AIR_RATIO
#else
    // No specific sensor defined, use generic defaults
    #define HMS_MQXXX_DEFAULT_A                 HMS_MQXXX_GENERIC_A_DEFAULT
    #define HMS_MQXXX_DEFAULT_B                 HMS_MQXXX_GENERIC_B_DEFAULT
    #define HMS_MQXXX_DEFAULT_MIN               HMS_MQXXX_GENERIC_MIN_DEFAULT
    #define HMS_MQXXX_DEFAULT_MAX               HMS_MQXXX_GENERIC_MAX_DEFAULT
    #define HMS_MQXXX_DEFAULT_TYPE              HMS_MQXXX_MQ2
    #define HMS_MQXXX_DEFAULT_REGRESSION        HMS_MQXXX_GENERIC_REGRESSION
    #define HMS_MQXXX_DEFAULT_CLEAN_AIR_RATIO   HMS_MQXXX_GENERIC_CLEAN_AIR_RATIO
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
    │ Gas-Specific: HMS_MQXXX_GET_GAS_A(HMS_MQXXX_MQ2, LPG);              │
    └─────────────────────────────────────────────────────────────────────┘
*/

// Basic sensor macros (uses default gas for each sensor)
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

#define HMS_MQXXX_GET_MIN_PPM(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_MIN_DEFAULT    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_MIN_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_MIN_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_MIN_DEFAULT : \
     HMS_MQXXX_GENERIC_MIN_DEFAULT)

#define HMS_MQXXX_GET_MAX_PPM(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_MAX_DEFAULT    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_MAX_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_MAX_DEFAULT  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_MAX_DEFAULT : \
     HMS_MQXXX_GENERIC_MAX_DEFAULT)

#define HMS_MQXXX_GET_REGRESSION(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_REGRESSION    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_REGRESSION  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_REGRESSION  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_REGRESSION : \
     HMS_MQXXX_GENERIC_REGRESSION)

#define HMS_MQXXX_GET_CLEAN_AIR_RATIO(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_CLEAN_AIR_RATIO    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_CLEAN_AIR_RATIO  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_CLEAN_AIR_RATIO  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_CLEAN_AIR_RATIO : \
     HMS_MQXXX_GENERIC_CLEAN_AIR_RATIO)

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Gas-Specific Access Macros                                 │
    │ Usage:   HMS_MQXXX_GET_GAS_A(HMS_MQXXX_MQ2, LPG)                    │
    │ Gases:   H2, CO, LPG, ALCOHOL, PROPANE (MQ2)                        │
    │          CO, CO2, NH3, TOLUENE, ACETONE, ALCOHOL (MQ135)            │
    │          O3, NO2, CL2 (MQ131)                                       │
    │          ETHANOL, HYDROGEN, ISO_BUTANE (MQ303A)                     │
    └─────────────────────────────────────────────────────────────────────┘
*/

// MQ-2 Gas-Specific Macros
#define HMS_MQXXX_MQ2_GET_A(gas) HMS_MQXXX_MQ2_A_##gas
#define HMS_MQXXX_MQ2_GET_B(gas) HMS_MQXXX_MQ2_B_##gas
#define HMS_MQXXX_MQ2_GET_MIN(gas) HMS_MQXXX_MQ2_MIN_##gas
#define HMS_MQXXX_MQ2_GET_MAX(gas) HMS_MQXXX_MQ2_MAX_##gas

// MQ-135 Gas-Specific Macros
#define HMS_MQXXX_MQ135_GET_A(gas) HMS_MQXXX_MQ135_A_##gas
#define HMS_MQXXX_MQ135_GET_B(gas) HMS_MQXXX_MQ135_B_##gas
#define HMS_MQXXX_MQ135_GET_MIN(gas) HMS_MQXXX_MQ135_MIN_##gas
#define HMS_MQXXX_MQ135_GET_MAX(gas) HMS_MQXXX_MQ135_MAX_##gas

// MQ-131 Gas-Specific Macros
#define HMS_MQXXX_MQ131_GET_A(gas) HMS_MQXXX_MQ131_A_##gas
#define HMS_MQXXX_MQ131_GET_B(gas) HMS_MQXXX_MQ131_B_##gas
#define HMS_MQXXX_MQ131_GET_MIN(gas) HMS_MQXXX_MQ131_MIN_##gas
#define HMS_MQXXX_MQ131_GET_MAX(gas) HMS_MQXXX_MQ131_MAX_##gas

// MQ-303A Gas-Specific Macros
#define HMS_MQXXX_MQ303A_GET_A(gas) HMS_MQXXX_MQ303A_A_##gas
#define HMS_MQXXX_MQ303A_GET_B(gas) HMS_MQXXX_MQ303A_B_##gas
#define HMS_MQXXX_MQ303A_GET_MIN(gas) HMS_MQXXX_MQ303A_MIN_##gas
#define HMS_MQXXX_MQ303A_GET_MAX(gas) HMS_MQXXX_MQ303A_MAX_##gas

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Range Validation Macros                                    │
    │ Usage:   if(HMS_MQXXX_IS_IN_RANGE(ppm_value, HMS_MQXXX_MQ2, LPG))   │
    └─────────────────────────────────────────────────────────────────────┘
*/
#define HMS_MQXXX_IS_IN_RANGE(ppm, sensor, gas) \
    ((ppm) >= HMS_MQXXX_##sensor##_MIN_##gas && (ppm) <= HMS_MQXXX_##sensor##_MAX_##gas)

#define HMS_MQXXX_IS_IN_DEFAULT_RANGE(ppm, sensor_type) \
    ((ppm) >= HMS_MQXXX_GET_MIN_PPM(sensor_type) && (ppm) <= HMS_MQXXX_GET_MAX_PPM(sensor_type))

/*
    ┌─────────────────────────────────────────────────────────────────────┐
    │ Note:    Heater & Compensation Helper Macros                        │
    │ Usage:   HMS_MQXXX_GET_HEATER_VOLTAGE(HMS_MQXXX_MQ2)                │
    │ Info:    Simple access to heater settings and compensation factors  │
    └─────────────────────────────────────────────────────────────────────┘
*/

// Heater Information Macros
#define HMS_MQXXX_GET_HEATER_VOLTAGE(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_HEATER_VOLTAGE    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_HEATER_VOLTAGE  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_HEATER_VOLTAGE  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_HEATER_VOLTAGE : \
     5.0f)

#define HMS_MQXXX_GET_PREHEAT_TIME(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_PREHEAT_TIME    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_PREHEAT_TIME  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_PREHEAT_TIME  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_PREHEAT_TIME : \
     180)

#define HMS_MQXXX_GET_BURN_IN_TIME(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_BURN_IN_TIME    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_BURN_IN_TIME  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_BURN_IN_TIME  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_BURN_IN_TIME : \
     24)

// Temperature Compensation Macros
#define HMS_MQXXX_GET_TEMP_COEFF(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_TEMP_COEFF    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_TEMP_COEFF  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_TEMP_COEFF  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_TEMP_COEFF : \
     HMS_MQXXX_TEMP_COEFF_GENERIC)

#define HMS_MQXXX_GET_HUMIDITY_COEFF(sensor_type) \
    ((sensor_type) == HMS_MQXXX_MQ2    ? HMS_MQXXX_MQ2_HUMIDITY_COEFF    : \
     (sensor_type) == HMS_MQXXX_MQ135  ? HMS_MQXXX_MQ135_HUMIDITY_COEFF  : \
     (sensor_type) == HMS_MQXXX_MQ131  ? HMS_MQXXX_MQ131_HUMIDITY_COEFF  : \
     (sensor_type) == HMS_MQXXX_MQ303A ? HMS_MQXXX_MQ303A_HUMIDITY_COEFF : \
     HMS_MQXXX_HUMIDITY_COEFF_GENERIC)

// Simple compensation calculation macros (optional usage)
#define HMS_MQXXX_TEMP_FACTOR(temp_celsius, sensor_type) \
    (1.0f + HMS_MQXXX_GET_TEMP_COEFF(sensor_type) * ((temp_celsius) - HMS_MQXXX_TEMP_BASELINE))

#define HMS_MQXXX_HUMIDITY_FACTOR(humidity_percent, sensor_type) \
    (1.0f + HMS_MQXXX_GET_HUMIDITY_COEFF(sensor_type) * ((humidity_percent) - HMS_MQXXX_HUMIDITY_BASELINE))

// Complete compensation calculation (for advanced users)
#define HMS_MQXXX_COMPENSATE_PPM(raw_ppm, temp_celsius, humidity_percent, sensor_type) \
    ((HMS_MQXXX_ENABLE_TEMP_COMPENSATION || HMS_MQXXX_ENABLE_HUMIDITY_COMPENSATION) ? \
     (raw_ppm) * \
     (HMS_MQXXX_ENABLE_TEMP_COMPENSATION ? HMS_MQXXX_TEMP_FACTOR(temp_celsius, sensor_type) : 1.0f) * \
     (HMS_MQXXX_ENABLE_HUMIDITY_COMPENSATION ? HMS_MQXXX_HUMIDITY_FACTOR(humidity_percent, sensor_type) : 1.0f) : \
     (raw_ppm))


#endif // HMS_MQXXX_CONFIG_H