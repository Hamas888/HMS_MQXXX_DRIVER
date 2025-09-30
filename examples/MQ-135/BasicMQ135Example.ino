/*
 * Basic MQ-135 Gas Sensor Example
 * 
 * This example demonstrates simple usage of the HMS_MQXXX driver
 * with an MQ-135 sensor for air quality monitoring.
 * 
 * MQ-135 detects: CO2, Ammonia, NOx, Alcohol, Benzene, Smoke
 * Perfect for air quality monitoring and indoor environment control.
 * 
 * Hardware Connections:
 * - VCC: 5V
 * - GND: Ground  
 * - A0:  Analog pin (A0 in this example)
 * - D0:  Digital pin (optional, not used here)
 */

#include "HMS_MQXXX_DRIVER.h"

// Create MQ-135 sensor instance
// Using default configuration from HMS_MQXXX_Config.h
HMS_MQXXX mq135(A0, HMS_MQXXX_MQ135);

void setup() {
  Serial.begin(9600);
  Serial.println("HMS MQ-135 Air Quality Sensor - Basic Example");
  Serial.println("==============================================");
  
  // Initialize the sensor
  if(mq135.init() == HMS_MQXXX_OK) {
    Serial.println("MQ-135 sensor initialized successfully!");
  } else {
    Serial.println("Failed to initialize MQ-135 sensor!");
    return;
  }
  
  Serial.println("Warming up sensor...");
  Serial.println("Please wait 20 seconds for sensor stabilization");
  
  // Warm-up period (important for accurate readings)
  delay(20000);
  
  Serial.println("Sensor ready!");
  Serial.println("Air quality measurements will be displayed every 3 seconds");
  Serial.println("Range: CO2 (10-10000 ppm), NH3 (1-500 ppm), CO (1-1000 ppm), Alcohol (1-500 ppm)");
  Serial.println();
}

void loop() {
  // Read sensor value (Rs/R0 ratio)
  float sensorRatio = mq135.readSensor();
  
  // Calculate gas concentrations in PPM for different gases
  // Set coefficients for CO2 and calculate
  mq135.setA(HMS_MQXXX_MQ135_A_CO2);
  mq135.setB(HMS_MQXXX_MQ135_B_CO2);
  float co2PPM = mq135.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for NH3 and calculate
  mq135.setA(HMS_MQXXX_MQ135_A_NH3);
  mq135.setB(HMS_MQXXX_MQ135_B_NH3);
  float nh3PPM = mq135.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for CO and calculate
  mq135.setA(HMS_MQXXX_MQ135_A_CO);
  mq135.setB(HMS_MQXXX_MQ135_B_CO);
  float coPPM = mq135.setRatioAndGetPPM(sensorRatio);
  
  // Set coefficients for Alcohol and calculate
  mq135.setA(HMS_MQXXX_MQ135_A_ALCOHOL);
  mq135.setB(HMS_MQXXX_MQ135_B_ALCOHOL);
  float alcoholPPM = mq135.setRatioAndGetPPM(sensorRatio);
  
  // Display results
  Serial.println("=== MQ-135 Air Quality ===");
  Serial.print("Sensor Ratio (Rs/R0): ");
  Serial.println(sensorRatio, 3);
  
  Serial.print("CO2:     ");
  Serial.print(co2PPM, 1);
  Serial.println(" ppm");
  
  Serial.print("NH3:     ");
  Serial.print(nh3PPM, 1);
  Serial.println(" ppm");
  
  Serial.print("CO:      ");
  Serial.print(coPPM, 1);
  Serial.println(" ppm");
  
  Serial.print("Alcohol: ");
  Serial.print(alcoholPPM, 1);
  Serial.println(" ppm");
  
  // Air quality assessment
  String airQuality = "Good";
  if (co2PPM > 800 || nh3PPM > 50 || coPPM > 30) {
    airQuality = "Poor";
    Serial.println("🔴 POOR AIR QUALITY!");
  } else if (co2PPM > 600 || nh3PPM > 25 || coPPM > 15) {
    airQuality = "Moderate";
    Serial.println("🟡 Moderate Air Quality");
  } else {
    Serial.println("🟢 Good Air Quality");
  }
  
  Serial.print("Overall: ");
  Serial.println(airQuality);
  Serial.println("---------------------------");
  
  delay(3000); // Read every 3 seconds
}