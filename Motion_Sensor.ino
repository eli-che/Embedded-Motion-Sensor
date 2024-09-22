#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // For I2C version of LCD

// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pirPin = 4;     // PIR sensor input pin (GPIO 4)
int pirState = LOW; // Default state of PIR (no motion detected)
int val = 0;        // Variable for reading PIR state

void setup() {
  // Initialize I2C and specify the custom SDA and SCL pins
  Wire.begin(5, 6); // SDA on GPIO 5, SCL on GPIO 6

  // Initialize the LCD
  lcd.begin(16, 2); // Specify the dimensions of the LCD (16 columns, 2 rows)
  lcd.backlight();  // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("System Ready");

  // Initialize PIR sensor
  pinMode(pirPin, INPUT);

  delay(2000); // Pause for 2 seconds
  lcd.clear(); // Clear the LCD after the intro message
}
void loop() {
  // Read the PIR sensor
  val = digitalRead(pirPin);

  // Print the PIR sensor value to the serial monitor
  Serial.print("PIR sensor value: ");
  Serial.println(val);

  if (val == HIGH) { 
    if (pirState == LOW) {
      // Motion detected
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MovementDetected");
      pirState = HIGH; // Update the state to HIGH
    }
  } else {
    if (pirState == HIGH) {
      // No motion detected
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Movement");
      pirState = LOW; // Update the state to LOW
    }
  }

  delay(500); // Small delay to avoid flickering on the LCD
}

