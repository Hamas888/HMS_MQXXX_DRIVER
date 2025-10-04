#include "HMS_MQXXX_DRIVER.h"


#if defined(HMS_MQXXX_PLATFORM_ARDUINO)
HMS_MQXXX::HMS_MQXXX(uint8_t pin, HMS_MQXXX_Type type) : pin(pin), type(type) {
  setDefaultValues();
}

HMS_MQXXX_StatusTypeDef HMS_MQXXX::init() {
  // For Arduino, set pin as INPUT
  pinMode(pin, INPUT);
  return HMS_MQXXX_OK;
}

#elif defined(HMS_MQXXX_PLATFORM_STM32_HAL)
HMS_MQXXX::HMS_MQXXX(ADC_HandleTypeDef *hadc, HMS_MQXXX_Type type) : type(type) {
  setDefaultValues();
  MQXXX_hadc = hadc;
}

HMS_MQXXX_StatusTypeDef HMS_MQXXX::init() {
  // For STM32, ADC is already configured in CubeMX
   if(MQXXX_hadc == NULL){
    return HMS_MQXXX_ERROR;
  }

  setRegressionMethod(regression);
  float calcR0 = 0;
  for(int i = 0; i<=HMS_CALIBRATIION_SAMPLES; i++)
    {
      calcR0 += calibrate(HMS_MQXXX_MQ2_CLEAN_AIR_RATIO,0);
    }
  setR0(calcR0/HMS_CALIBRATIION_SAMPLES);  
  // Just initialize any required variables
  readSensor()
  return HMS_MQXXX_OK;
}

#elif defined(HMS_MQXXX_PLATFORM_ESP_IDF)
HMS_MQXXX::HMS_MQXXX(uint8_t pin, HMS_MQXXX_Type type) : pin(pin), type(type) {
  setDefaultValues();
}

HMS_MQXXX_StatusTypeDef HMS_MQXXX::init() {
  // Initialize ESP-IDF ADC
  return HMS_MQXXX_OK;
}

#elif defined(HMS_MQXXX_PLATFORM_ZEPHYR)
HMS_MQXXX::HMS_MQXXX(uint8_t pin, HMS_MQXXX_Type type) : pin(pin), type(type) {
  setDefaultValues();
}

HMS_MQXXX_StatusTypeDef HMS_MQXXX::init() {
  // Initialize Zephyr ADC
  return HMS_MQXXX_OK;
}
#endif

void HMS_MQXXX::setDefaultValues() {
  switch(type) {
    case HMS_MQXXX_MQ2:
      a = HMS_MQXXX_MQ2_A_DEFAULT;
      b = HMS_MQXXX_MQ2_B_DEFAULT;
      regression = HMS_MQXXX_MQ2_REGRESSION;
      break;
    case HMS_MQXXX_MQ135:
      a = HMS_MQXXX_MQ135_A_DEFAULT;
      b = HMS_MQXXX_MQ135_B_DEFAULT;
      regression = HMS_MQXXX_MQ135_REGRESSION;
      break;
    case HMS_MQXXX_MQ131:
      a = HMS_MQXXX_MQ131_A_DEFAULT;
      b = HMS_MQXXX_MQ131_B_DEFAULT;
      regression = HMS_MQXXX_MQ131_REGRESSION;
      break;
    case HMS_MQXXX_MQ303A:
      a = HMS_MQXXX_MQ303A_A_DEFAULT;
      b = HMS_MQXXX_MQ303A_B_DEFAULT;
      regression = HMS_MQXXX_MQ303A_REGRESSION;
      break;
    default:
      a = HMS_MQXXX_GENERIC_A_DEFAULT;
      b = HMS_MQXXX_GENERIC_B_DEFAULT;
      regression = HMS_MQXXX_GENERIC_REGRESSION;
      break;
  }
  setA(a);
  setB(b);
}

static inline bool willOverflow(double log_ppm) {
  static const double maxLog = log10((double)FLT_MAX);
  static const double minLog = log10((double)FLT_MIN);
  return (log_ppm > maxLog || log_ppm < minLog);
}

static inline double safePow(double base, double exp){
  if(exp == 0.0) return 1.0;
  if(exp == 1.0) return base;
  if(exp == 2.0) return base * base;
  return pow(base, exp);
}

void HMS_MQXXX::mqDelay(uint32_t ms) {
    #if defined(HMS_MQXXX_PLATFORM_ARDUINO)
        delay(ms);
    #elif defined(HMS_MQXXX_PLATFORM_ESP_IDF)
        vTaskDelay(ms / portTICK_PERIOD_MS);
    #elif defined(HMS_MQXXX_PLATFORM_ZEPHYR)
        k_msleep(ms);
    #elif defined(HMS_MQXXX_PLATFORM_STM32_HAL)
        HAL_Delay(ms);
    #endif
}

void HMS_MQXXX::setA(float value) {
  if(isinf(value) || isnan(value)) {
    a = 0;
  } else if(value > HMS_MQXXX_MAX_A) {
    a = HMS_MQXXX_MAX_A;
  } else if(value < -HMS_MQXXX_MAX_A) {
    a = -HMS_MQXXX_MAX_A;
  } else {
    a = value;
  }
}

void HMS_MQXXX::setB(float value) {
  if(isinf(value) || isnan(value)) {
    b = 0;
  } else if(value > HMS_MQXXX_MAX_B) {
    b = HMS_MQXXX_MAX_B;
  } else if(value < -HMS_MQXXX_MAX_B) {
    b = -HMS_MQXXX_MAX_B;
  } else {
    b = value;
  }
}

float HMS_MQXXX::setRsR0RatioGetPPM(float value) {
  return setRatioAndGetPPM(value);
}

float HMS_MQXXX::getRS() {
  sensorVolt = getVoltage(true, false, 0);                                 // Read the voltage from the sensor
  rsCalc = ((vcc * rl) / sensorVolt) - rl;                              // Get value of RS in a gas
  if(rsCalc < 0)  rsCalc = 0;                                           // No negative values accepted.
  return rsCalc;
}

float HMS_MQXXX::getVoltage(bool read, bool injected, int value) {
  float voltage;
  if(read) {
    float avg = 0.0;

    for (int i = 0; i < retries; i++) {
        #if defined(HMS_MQXXX_PLATFORM_ARDUINO)
            adc = analogRead(pin);
        #elif defined(HMS_MQXXX_PLATFORM_STM32_HAL)
            // STM32 HAL ADC reading - assumes ADC is configured in CubeMX
            HAL_ADC_Start(MQXXX_hadc);
            HAL_ADC_PollForConversion(&MQXXX_hadc, 10);
            adc = HAL_ADC_GetValue(MQXXX_hadc); // User needs to adapt this
            //adc = 2048; // Placeholder - needs actual HAL implementation
        #elif defined(HMS_MQXXX_PLATFORM_ESP_IDF)
            // ESP-IDF ADC reading - needs ADC configuration
            adc = 2048; // Placeholder - needs actual ESP-IDF implementation
        #elif defined(HMS_MQXXX_PLATFORM_ZEPHYR)
            // Zephyr ADC reading - needs ADC device binding
            adc = 2048; // Placeholder - needs actual Zephyr implementation
        #endif
        avg += adc;
        mqDelay(retryInterval);
    }
    #if defined(HMS_MQXXX_PLATFORM_STM32_HAL)
    HAL_ADC_Stop(MQXXX_hadc);
    #endif

    voltage = (avg / retries) * voltageResolution / ((pow(2, adcBitResolution)) - 1);
    sensorVolt = voltage; // Update the sensor voltage
  }
  else if(injected) {
    // External voltage injection (for testing or external ADC)
    voltage = (value) * voltageResolution / ((pow(2, adcBitResolution)) - 1);
    sensorVolt = voltage;
  } else {
    // Return cached voltage
    voltage = sensorVolt;
  }
  return voltage;
}

// Simplified read sensor function - always reads fresh data
float HMS_MQXXX::readSensor(float correctionFactor) {
  // Special voltage adjustment for MQ303A
  if(type == HMS_MQXXX_MQ303A) {
    vcc = vcc - 0.45; // Adjust VCC for MQ303A calculations
  }

  // Get fresh sensor resistance reading
  getRS();

  // Automatic ratio calculation based on sensor type
  if(type == HMS_MQXXX_MQ131) {
    ratio = r0 / rsCalc;        // R0/Rs ratio for MQ-131 (inverted)
  } else {
    ratio = rsCalc / r0;        // Rs/R0 ratio for other sensors (MQ-2, MQ-135, MQ-303A)
  }
  
  ratio += correctionFactor;
  if(ratio <= 0) ratio = 0.001; // Prevent division by zero, use small positive value

  double tempPPM, logPPM;
  if(regression == HMS_MQXXX_EXPONENTIAL) {
    if(ratio <= 0 || a == 0) return 0;
    // PPM = a * ratio^b (exponential form)
    logPPM = log10((double)a) + (double)b * log10((double)ratio);
    if(willOverflow(logPPM)) 
      tempPPM = (logPPM > 0) ? FLT_MAX : 0.0;
    else 
      tempPPM = safePow(10.0, logPPM);
  } else {
    if(ratio <= 0 || a == 0) return 0;
    // PPM = 10^((log(ratio) - b) / a) (linear form)
    logPPM = (log10((double)ratio) - (double)b)/(double)a;
    if(willOverflow(logPPM)) 
      tempPPM = (logPPM > 0) ? FLT_MAX : 0.0;
    else 
      tempPPM = safePow(10.0, logPPM);
  }

  // Restore VCC if it was adjusted
  if(type == HMS_MQXXX_MQ303A) {
    vcc = vcc + 0.45;
  }

  if(tempPPM < 0) tempPPM = 0;
  if(isinf(tempPPM) || isnan(tempPPM)) tempPPM = FLT_MAX;

  ppm = (float)tempPPM;
  return ppm;
}

// Function to set ratio manually and calculate PPM (for external calculations)
float HMS_MQXXX::setRatioAndGetPPM(float ratioValue) {
  ratio = ratioValue;
  
  double tempPPM, logPPM;
  if(regression == HMS_MQXXX_EXPONENTIAL) {
    if(ratio <= 0 || a == 0) return 0;
    logPPM = log10((double)a) + (double)b * log10((double)ratio);
    if(willOverflow(logPPM)) 
      tempPPM = (logPPM > 0) ? FLT_MAX : 0.0;
    else 
      tempPPM = safePow(10.0, logPPM);
  } else {
    if(ratio <= 0 || a == 0) return 0;
    logPPM = (log10((double)ratio) - (double)b)/(double)a;
    if(willOverflow(logPPM)) 
      tempPPM = (logPPM > 0) ? FLT_MAX : 0.0;
    else 
      tempPPM = safePow(10.0, logPPM);
  }

  if(tempPPM < 0) tempPPM = 0;
  if(isinf(tempPPM) || isnan(tempPPM)) tempPPM = FLT_MAX;

  ppm = (float)tempPPM;
  return ppm;
}

float HMS_MQXXX::calibrate(float ratioInCleanAir, float correctionFactor) {
  // Read fresh voltage for calibration
  sensorVolt = getVoltage(true, false, 0);
  
  float tempRSAir;
  float temR0;
  tempRSAir = ((vcc * rl) / sensorVolt) - rl;
  if(tempRSAir < 0) tempRSAir = 0;
  temR0 = tempRSAir / ratioInCleanAir;
  temR0 += correctionFactor;
  if(temR0 < 0) temR0 = 0;
  
  // Automatically set the calculated R0 value
  r0 = temR0;
  
  return temR0;
}