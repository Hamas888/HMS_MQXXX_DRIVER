/*
 * Example: Config-Based Setup for HMS_MQXXX Driver
 * 
 * This example demonstrates how to use the macro-based configuration
 * system for easy sensor setup and customization.
 * 
 * Author: Hamas Saeed
 * Date: Sep 29, 2025
 */

// Step 1: Uncomment your sensor type in HMS_MQXXX_Config.h
// #define HMS_MQXXX_MQ2      // <- Uncomment this line in config file

#include "HMS_MQXXX_DRIVER.h"

// Method 1: Using default sensor from config (recommended)
HMS_MQXXX sensor1(A0);  // Uses HMS_MQXXX_DEFAULT_TYPE from config

// Method 2: Override sensor type explicitly  
HMS_MQXXX sensor2(A1, HMS_MQXXX_MQ135);  // Force MQ135 regardless of config

// Method 3: For multiple sensors of different types
HMS_MQXXX mq2_sensor(A0, HMS_MQXXX_MQ2);
HMS_MQXXX mq135_sensor(A1, HMS_MQXXX_MQ135);
HMS_MQXXX mq131_sensor(A2, HMS_MQXXX_MQ131);

void setup() {
    Serial.begin(9600);
    
    // Initialize all sensors
    sensor1.init();
    sensor2.init();
    mq2_sensor.init();
    mq135_sensor.init();
    mq131_sensor.init();
    
    // Example: Print default values for each sensor type
    Serial.println("=== Sensor Default Values ===");
    
    Serial.print("MQ2 - A: ");    Serial.print(HMS_MQXXX_MQ2_A_DEFAULT);
    Serial.print(", B: ");        Serial.println(HMS_MQXXX_MQ2_B_DEFAULT);
    
    Serial.print("MQ135 - A: ");  Serial.print(HMS_MQXXX_MQ135_A_DEFAULT);
    Serial.print(", B: ");        Serial.println(HMS_MQXXX_MQ135_B_DEFAULT);
    
    Serial.print("MQ131 - A: ");  Serial.print(HMS_MQXXX_MQ131_A_DEFAULT);
    Serial.print(", B: ");        Serial.println(HMS_MQXXX_MQ131_B_DEFAULT);
    
    // Example: Runtime sensor configuration using macros
    float runtime_a = HMS_MQXXX_GET_A(HMS_MQXXX_MQ2);
    float runtime_b = HMS_MQXXX_GET_B(HMS_MQXXX_MQ2);
    
    Serial.print("Runtime MQ2 - A: "); Serial.print(runtime_a);
    Serial.print(", B: ");              Serial.println(runtime_b);
    
    // Example: Override default values if needed
    sensor1.setA(500.0);  // Custom 'a' value
    sensor1.setB(-2.5);   // Custom 'b' value
    
    Serial.println("\nSensors initialized successfully!");
    Serial.println("Ready to read gas concentrations...");
}

void loop() {
    // Read from different sensors
    float ppm1 = sensor1.readSensor();
    float ppm2 = mq135_sensor.readSensor();
    float ppm3 = mq131_sensor.readSensor();
    
    Serial.print("Sensor1 (config default): "); Serial.print(ppm1); Serial.println(" ppm");
    Serial.print("MQ135: ");                     Serial.print(ppm2); Serial.println(" ppm");
    Serial.print("MQ131: ");                     Serial.print(ppm3); Serial.println(" ppm");
    
    delay(2000);
}

/*
 * Configuration Examples in HMS_MQXXX_Config.h:
 * 
 * // For MQ2 as default:
 * #define HMS_MQXXX_MQ2
 * 
 * // For MQ135 as default:
 * #define HMS_MQXXX_MQ135
 * 
 * // For custom calibration constants:
 * #define HMS_MQXXX_MQ2_A_DEFAULT    600.0f
 * #define HMS_MQXXX_MQ2_B_DEFAULT    -2.1f
 */