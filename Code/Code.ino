#include <LiquidCrystal.h>

// LCD pin assignments
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int batteryPin = A0;                                  // Analog pin for battery voltage
const int buzzerPin = 8;                                    // Digital pin for LED
const float lowBatteryThreshold = 3.8;                      // Low battery threshold (Volts)
const float R1 = 1000.0;                                    // R1 = 1k ohm
const float R2 = 10000.0;                                   // R2 = 10k ohm

void setup() {
  lcd.begin(16, 2);          
  pinMode(buzzerPin, OUTPUT);  
  Serial.begin(9600);        
}

void loop() {
  // Read the analog value
  int sensorValue = analogRead(batteryPin);

  // Convert the analog reading to voltage
  float voltage = sensorValue * (5.0 / 1023.0);             // Raw voltage
  float batteryVoltage = voltage / (R2/(R1+R2));            // Calculate battery voltage

  // Display the voltage on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Battery: ");
  lcd.print(batteryVoltage);
  lcd.print(" V");

  // Check for low battery and activate LED
  if (batteryVoltage < lowBatteryThreshold) {
    digitalWrite(buzzerPin, HIGH);                          // Activate LED
    lcd.setCursor(0, 1);
    lcd.print("LOW BATTERY!");
  } else {
    digitalWrite(buzzerPin, LOW);                           // Deactivate LED
    lcd.setCursor(0, 1);
    lcd.print("                ");                          //Clear second line
  }

  Serial.print("Raw ADC: ");
  Serial.print(sensorValue);
    Serial.print(" Scaled Voltage: ");
  Serial.print(voltage);
  Serial.print(" Battery Voltage: ");
  Serial.println(batteryVoltage);
  delay(1000); 
}
