/*
 * Basic MQ-2 Gas Sensor Example
 * 
 * This example demonstrates simple usage of the HMS_MQXXX driver
 * with an MQ-2 sensor to detect combustible gases like LPG, Smoke, and Alcohol.
 * 
 * MQ-2 detects: LPG, Smoke, Alcohol, Propane, Hydrogen, Methane
 * 
 * Hardware Connections:
 * - VCC: 5V
 * - GND: Ground
 * - A0:  Analog pin (A0 in this example)
 * - D0:  Digital pin (optional, not used here)
 */

#include "HMS_MQXXX_DRIVER.h"

// Create MQ-2 sensor instance
// Using default configuration from HMS_MQXXX_Config.h
HMS_MQXXX mq2(A0, HMS_MQXXX_MQ2);

void setup() {
  Serial.begin(9600);
  Serial.println("HMS MQ-2 Gas Sensor - Basic Example");
  Serial.println("===================================");
  
  // Initialize the sensor
  if(mq2.init() == HMS_MQXXX_OK) {
    Serial.println("MQ-2 sensor initialized successfully!");
  } else {
    Serial.println("Failed to initialize MQ-2 sensor!");
    return;
  }
  
  Serial.println("Warming up sensor...");
  Serial.println("Please wait 20 seconds for sensor stabilization");
  
  // Warm-up period (important for accurate readings)
  delay(20000);
  
  Serial.println("Sensor ready!");
  Serial.println("Gas concentrations will be displayed every 2 seconds");
  Serial.println("Range: LPG (300-10000 ppm), CO (20-2000 ppm), Alcohol (100-2000 ppm), H2 (300-5000 ppm)");
  Serial.println();
}

void loop() {
  // Read sensor value (Rs/R0 ratio)
  float sensorRatio = mq2.readSensor();
  
  // Calculate gas concentrations in PPM for different gases
  // Set coefficients for LPG and calculate
  mq2.setA(HMS_MQXXX_MQ2_A_LPG);
  mq2.setB(HMS_MQXXX_MQ2_B_LPG);
  float lpgPPM = mq2.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for CO and calculate
  mq2.setA(HMS_MQXXX_MQ2_A_CO);
  mq2.setB(HMS_MQXXX_MQ2_B_CO);
  float coPPM = mq2.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for Alcohol and calculate
  mq2.setA(HMS_MQXXX_MQ2_A_ALCOHOL);
  mq2.setB(HMS_MQXXX_MQ2_B_ALCOHOL);
  float alcoholPPM = mq2.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for H2 and calculate
  mq2.setA(HMS_MQXXX_MQ2_A_H2);
  mq2.setB(HMS_MQXXX_MQ2_B_H2);
  float h2PPM = mq2.setRatioAndGetPPM(sensorRatio);
  
  // Display results
  Serial.println("=== MQ-2 Gas Detection ===");
  Serial.print("Sensor Ratio (Rs/R0): ");
  Serial.println(sensorRatio, 3);
  
  Serial.print("LPG:     ");
  Serial.print(lpgPPM, 1);
  Serial.println(" ppm");
  
  Serial.print("CO:      ");
  Serial.print(coPPM, 1);
  Serial.println(" ppm");
  
  Serial.print("Alcohol: ");
  Serial.print(alcoholPPM, 1);
  Serial.println(" ppm");
  
  Serial.print("H2:      ");
  Serial.print(h2PPM, 1);
  Serial.println(" ppm");
  
  // Simple threshold alerts
  if (lpgPPM > 1000) {
    Serial.println("⚠️  HIGH LPG DETECTED!");
  }
  if (coPPM > 50) {
    Serial.println("⚠️  HIGH CO DETECTED!");
  }
  if (alcoholPPM > 500) {
    Serial.println("⚠️  HIGH ALCOHOL DETECTED!");
  }
  
  Serial.println("-------------------------");
  
  delay(2000); // Read every 2 seconds
}