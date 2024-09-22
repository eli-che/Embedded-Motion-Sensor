# Embedded Motion Sensor

This project demonstrates a proof-of-concept (PoC) test of a PIR (Passive Infrared) motion detector interfaced with an ESP32 and a 16x2 I2C LCD. The system detects movement and displays the motion status on the LCD, providing visual feedback when motion is detected or not.

## Features

https://github.com/user-attachments/assets/0d5bda71-69ed-4d07-b7d7-7d53d38d2aa3

- **PIR Motion Detection**: Detects movement using a PIR sensor.
- **LCD Display**: Displays the status of motion detection ("Movement Detected" or "No Movement") on a 16x2 I2C LCD.
- **Serial Output**: Outputs PIR sensor values to the serial monitor for debugging.

## Components
- **ESP32 (ESP32-S3-WROOM)**
- **PIR Motion Sensor**
- **16x2 I2C LCD**
- **Wires & Breadboard**

## Pin Configuration

| Component         | GPIO Pin      | Function          |
|-------------------|---------------|-------------------|
| PIR Sensor Output  | GPIO 4        | Reads motion detection status |
| LCD SDA            | GPIO 5        | I2C Data Line     |
| LCD SCL            | GPIO 6        | I2C Clock Line    |

## Circuit Diagram
- Connect the PIR sensor's output pin to GPIO 4 of the ESP32.
- Connect the I2C LCD's SDA to GPIO 5 and SCL to GPIO 6.

## Code Explanation
The project uses the **LiquidCrystal_I2C** library to interface with the LCD and read the motion detection status from the PIR sensor. When the sensor detects motion, the LCD displays "Movement Detected." When no motion is detected, the LCD displays "No Movement."

```cpp
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pirPin = 4;     // PIR sensor input pin (GPIO 4)
int pirState = LOW; // Default state of PIR (no motion detected)
int val = 0;        // Variable for reading PIR state

void setup() {
  // Initialize I2C and specify the custom SDA and SCL pins
  Wire.begin(5, 6); // SDA on GPIO 5, SCL on GPIO 6

  // Initialize the LCD
  lcd.begin(16, 2); 
  lcd.backlight();  
  lcd.print("System Ready");

  // Initialize PIR sensor
  pinMode(pirPin, INPUT);

  delay(2000); 
  lcd.clear(); 
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
      lcd.print("MovementDetected");
      pirState = HIGH; 
    }
  } else {
    if (pirState == HIGH) {
      // No motion detected
      lcd.clear();
      lcd.print("No Movement");
      pirState = LOW; 
    }
  }

  delay(500); 
}
```

## How to Use
1. **Hardware Setup**:
   - Connect the PIR sensor and LCD according to the pin configuration table.
2. **Software Setup**:
   - Install the required **LiquidCrystal_I2C** library: [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C).
   - Upload the provided code to your ESP32 using the Arduino IDE.
3. **Run the Project**:
   - Open the serial monitor to observe the PIR sensor values.
   - The LCD will display the current motion detection status in real-time.

## Future Improvements
- Add buzzer feedback or LED indication for motion detection.
- Integrate a timer to automatically reset the system after a certain period of no motion.
- Extend the range of the motion detection by using additional PIR sensors.

## License
This project is open-source under the MIT License. Feel free to modify and distribute as needed.
