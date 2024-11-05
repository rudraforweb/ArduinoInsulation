#include <DHT22.h>
#include "Arduino_LED_Matrix.h"
#include <SparkFun_Qwiic_Button.h>
#include <SparkFun_Qwiic_OLED.h> 
#include <string> 


//define pin data
#define pinDATA A0
#define pinMAIN A1 // SDA, or almost any other I/O pin

DHT22 dht22(pinDATA); 
DHT22 main22(pinMAIN); 

ArduinoLEDMatrix matrix;
QwiicButton button;
QwiicNarrowOLED myOLED;

unsigned long previousLogTime = 0;
int loopCounter = 0;  // Counter for loop iterations
int logCounter = 1; 


uint8_t brightness = 250;   //The maximum brightness of the pulsing LED. Can be between 0 (min) and 255 (max)
uint16_t cycleTime = 1000;   //The total time for the pulse to take. Set to a bigger number for a slower pulse, or a smaller number for a faster pulse
uint16_t offTime = 200;   

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //1bit=10µs
  Wire1.begin();

  
  if (myOLED.begin(Wire1) == false)
    {
        Serial.println("Display begin failed. Freezing...");
        while (true)
            ;
    }
    Serial.println("Display READY");
  if (button.begin(SFE_QWIIC_BUTTON_DEFAULT_ADDRESS, Wire1) == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button READY");
  button.LEDoff();

  matrix.begin();
  myOLED.erase();
  myOLED.setCursor(0, 0);
  myOLED.text(0, 0, "Ready!", 1);
  myOLED.text(0, 10, "Press the button", 1);
  myOLED.text(0, 20,"to start testing.", 1);
  myOLED.display();
  Serial.println("ArduinoInsulation");
  Serial.println("IGNORE LOG 0.");
  Serial.println("-------------------------------------------");

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();
  String tempStr = String(t);


  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Connect COTTON to A0, then press button again when ready.");
  myOLED.erase();
  myOLED.text(0, 0, "Connect COTTON to A0", 1);
  myOLED.text(0, 10, "Press button again", 1);
  myOLED.text(0, 20,"when ready", 1);
  myOLED.display();
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Heat up the box to 40 degrees.");
  while (button.isPressed() == false) {
    myOLED.erase();
    myOLED.text(0, 0, "Heat up the box", 1);
    myOLED.text(0, 10, "to 40 degrees|", 1);
    float t = dht22.getTemperature();
    String tempStr = String(t);
    myOLED.text(90, 10, tempStr, 1);
    myOLED.text(0, 20, "Press to start COTTON", 1);
    myOLED.display();
    delay(100);
      button.LEDconfig(brightness, cycleTime, offTime);
      button.LEDon(20);
      if (button.isPressed() == true) {
        break;
      }
    }
  Serial.println("-----------------------------------------");
  Serial.println("Test started: COTTON");
  delay(2000);
  myOLED.erase();
  
  unsigned long previousLogTime = 0;
  int logCounter = 0;  // Counter for logged entries

    for (int i = 0; i < 6; i++) {  // Run the loop 5 times
        // Erase previous display contents
        myOLED.erase();

        // Display the current temperature reading
        float currentTemp = dht22.getTemperature();
        String currentTempStr = String(currentTemp);
        myOLED.text(0, 0, "Temps: COTTON ", 1);
        myOLED.display();

        // Log temperature every 5 minutes
        String logEntry = String(logCounter);  // Convert log count to string
        myOLED.text(50, 10, "LOG", 1);
        
        myOLED.text(80, 10, logEntry, 1);
        myOLED.text(0, 10, currentTempStr, 1);  // Display logged temperature
        myOLED.display();

        // Print log info to Serial
        Serial.println("LOG "+ logEntry +" Temperature: " + currentTempStr);
        logCounter++;  // Increment log count for the next entry

        // Wait for 5 minutes (300000 milliseconds)
        delay(300000);
    }
  Serial.println("Test finished: COTTON");
  button.LEDconfig(brightness, cycleTime, offTime);
  Serial.println("-----------------------------------------------");
  myOLED.text(0, 20, "Finished:Press button", 1);
  myOLED.display();
  
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  Serial.println("Connect WOOL to A0, then press button again when ready.");
  myOLED.erase();
  myOLED.text(0, 0, "Connect WOOL to A0", 1);
  myOLED.text(0, 10, "Press button again", 1);
  myOLED.text(0, 20,"when ready", 1);
  myOLED.display();
  delay(1000);
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Heat up the box to 40 degrees");
  while (button.isPressed() == false) {
    myOLED.erase();
    myOLED.text(0, 0, "Heat up the box", 1);
    myOLED.text(0, 10, "to 40 degrees|", 1);
    float t = dht22.getTemperature();
    String tempStr = String(t);
    myOLED.text(90, 10, tempStr, 1);
    myOLED.text(0, 20, "Press to start COTTON", 1);
    myOLED.display();
    delay(100);
      button.LEDconfig(brightness, cycleTime, offTime);
      button.LEDon(20);
      if (button.isPressed() == true) {
        break;
      }
    }
  Serial.println("-------------------------------------");
  Serial.println("Test started: WOOL");
  previousLogTime = 0;
  logCounter = 0;
  for (int i = 0; i < 6; i++) {  // Run the loop 5 times
        // Erase previous display contents
        myOLED.erase();

        // Display the current temperature reading
        float currentTemp = dht22.getTemperature();
        String currentTempStr = String(currentTemp);
        myOLED.text(0, 0, "Temps: WOOL ", 1);
        myOLED.display();

        // Log temperature every 5 minutes
        String logEntry = String(logCounter);  // Convert log count to string
        myOLED.text(50, 10, "LOG", 1);
        
        myOLED.text(80, 10, logEntry, 1);
        myOLED.text(0, 10, currentTempStr, 1);  // Display logged temperature
        myOLED.display();

        // Print log info to Serial
        Serial.println("LOG "+ logEntry +" Temperature: " + currentTempStr);
        logCounter++;  // Increment log count for the next entry

        // Wait for 5 minutes (300000 milliseconds)
        delay(300000);
    }

  myOLED.text(0, 20, "Finished:Press button", 1);
  Serial.println("Test finished: WOOL");
  button.LEDconfig(brightness, cycleTime, offTime);
  Serial.println("-------------------------------------------");
  myOLED.display();
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  Serial.println("Connect REPAPER (RECYCLEDPAPER) to A0, then press button again when ready.");
  myOLED.erase();
  myOLED.text(0, 0, "Connect REPAPER to A0", 1);
  myOLED.text(0, 10, "Press button again", 1);
  myOLED.text(0, 20,"when ready", 1);
  myOLED.display();
  delay(1000);
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Heat up the box to 40 degrees");
  while (button.isPressed() == false) {
    myOLED.erase();
    myOLED.text(0, 0, "Heat up the box", 1);
    myOLED.text(0, 10, "to 40 degrees|", 1);
    float t = dht22.getTemperature();
    String tempStr = String(t);
    myOLED.text(90, 10, tempStr, 1);
    myOLED.text(0, 20, "Press to startREPAPER", 1);
    myOLED.display();
    delay(100);
      button.LEDconfig(brightness, cycleTime, offTime);
      button.LEDon(20);
      if (button.isPressed() == true) {
        break;
      }
    }
  Serial.println("-------------------------------------");
  Serial.println("Test started: REPAPER");
  previousLogTime = 0;
  logCounter = 0;
  for (int i = 0; i < 6; i++) {  // Run the loop 5 times
        // Erase previous display contents
        myOLED.erase();

        // Display the current temperature reading
        float currentTemp = dht22.getTemperature();
        String currentTempStr = String(currentTemp);
        myOLED.text(0, 0, "Temps: REPAPER ", 1);
        myOLED.display();

        // Log temperature every 5 minutes
        String logEntry = String(logCounter);  // Convert log count to string
        myOLED.text(50, 10, "LOG", 1);
        
        myOLED.text(80, 10, logEntry, 1);
        myOLED.text(0, 10, currentTempStr, 1);  // Display logged temperature
        myOLED.display();

        // Print log info to Serial
        Serial.println("LOG "+ logEntry +" Temperature: " + currentTempStr);
        logCounter++;  // Increment log count for the next entry

        // Wait for 5 minutes (300000 milliseconds)
        delay(300000);
    }

  myOLED.text(0, 20, "Finished:Press button", 1);
  Serial.println("Test finished: REPAPER");
  button.LEDconfig(brightness, cycleTime, offTime);
  Serial.println("-------------------------------------------");
  myOLED.display();
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  Serial.println("Connect SFOAM (STYROFOAM) to A0, then press button again when ready.");
  myOLED.erase();
  myOLED.text(0, 0, "Connect SFOAM to A0", 1);
  myOLED.text(0, 10, "Press button again", 1);
  myOLED.text(0, 20,"when ready", 1);
  myOLED.display();
  delay(1000);
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Heat up the box to 40 degrees");
  while (button.isPressed() == false) {
    myOLED.erase();
    myOLED.text(0, 0, "Heat up the box", 1);
    myOLED.text(0, 10, "to 40 degrees|", 1);
    float t = dht22.getTemperature();
    String tempStr = String(t);
    myOLED.text(90, 10, tempStr, 1);
    myOLED.text(0, 20, "Press to start SFOAM", 1);
    myOLED.display();
    delay(100);
      button.LEDconfig(brightness, cycleTime, offTime);
      button.LEDon(20);
      if (button.isPressed() == true) {
        break;
      }
    }
  Serial.println("-------------------------------------");
  Serial.println("Test started: SFOAM");
  previousLogTime = 0;
  logCounter = 0;
  for (int i = 0; i < 6; i++) {  // Run the loop 5 times
        // Erase previous display contents
        myOLED.erase();

        // Display the current temperature reading
        float currentTemp = dht22.getTemperature();
        String currentTempStr = String(currentTemp);
        myOLED.text(0, 0, "Temps: SFOAM ", 1);
        myOLED.display();

        // Log temperature every 5 minutes
        String logEntry = String(logCounter);  // Convert log count to string
        myOLED.text(50, 10, "LOG", 1);
        
        myOLED.text(80, 10, logEntry, 1);
        myOLED.text(0, 10, currentTempStr, 1);  // Display logged temperature
        myOLED.display();

        // Print log info to Serial
        Serial.println("LOG "+ logEntry +" Temperature: " + currentTempStr);
        logCounter++;  // Increment log count for the next entry

        // Wait for 5 minutes (300000 milliseconds)
        delay(300000);
    }

  myOLED.text(0, 20, "Finished:Press button", 1);
  Serial.println("Test finished: SFOAM");
  button.LEDconfig(brightness, cycleTime, offTime);
  Serial.println("-------------------------------------------");
  myOLED.display();
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  Serial.println("Connect CTRL (CONTROL) to A0, then press button again when ready.");
  myOLED.erase();
  myOLED.text(0, 0, "Connect CTRL to A0", 1);
  myOLED.text(0, 10, "Press button again", 1);
  myOLED.text(0, 20,"when ready", 1);
  myOLED.display();
  delay(1000);
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  delay(1000);
  Serial.println("Heat up the box to 40 degrees");
  while (button.isPressed() == false) {
    myOLED.erase();
    myOLED.text(0, 0, "Heat up the box", 1);
    myOLED.text(0, 10, "to 40 degrees|", 1);
    float t = dht22.getTemperature();
    String tempStr = String(t);
    myOLED.text(90, 10, tempStr, 1);
    myOLED.text(0, 20, "Press to start CTRL", 1);
    myOLED.display();
    delay(100);
      button.LEDconfig(brightness, cycleTime, offTime);
      button.LEDon(20);
      if (button.isPressed() == true) {
        break;
      }
    }
  Serial.println("-------------------------------------");
  Serial.println("Test started: CTRL");
  previousLogTime = 0;
  logCounter = 0;
  for (int i = 0; i < 6; i++) {  // Run the loop 5 times
        // Erase previous display contents
        myOLED.erase();

        // Display the current temperature reading
        float currentTemp = dht22.getTemperature();
        String currentTempStr = String(currentTemp);
        myOLED.text(0, 0, "Temps: CTRL ", 1);
        myOLED.display();

        // Log temperature every 5 minutes
        String logEntry = String(logCounter);  // Convert log count to string
        myOLED.text(50, 10, "LOG", 1);
        
        myOLED.text(80, 10, logEntry, 1);
        myOLED.text(0, 10, currentTempStr, 1);  // Display logged temperature
        myOLED.display();

        // Print log info to Serial
        Serial.println("LOG "+ logEntry +" Temperature: " + currentTempStr);
        logCounter++;  // Increment log count for the next entry

        // Wait for 5 minutes (300000 milliseconds)
        delay(300000);
    }

  myOLED.text(0, 20, "Finished:Press button", 1);
  Serial.println("Test finished: CTRL");
  button.LEDconfig(brightness, cycleTime, offTime);
  Serial.println("-------------------------------------------");
  myOLED.display();

  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  myOLED.erase();
  myOLED.text(0, 0, "Check Serial Monitor", 1);
  myOLED.text(0, 10, "for values.", 1);
  myOLED.text(0, 20, "Press for nextpage", 1);
  myOLED.display();
  delay(1000);
  while (button.isPressed() == false) {
      button.LEDconfig(brightness, cycleTime, offTime);
      if (button.isPressed() == true) {
        button.LEDon(20);
        break;
      }
    }
  myOLED.erase();
  myOLED.text(0, 0, "Press RESET to do ", 1);
  myOLED.text(0, 10, "more test runs.", 1);
  myOLED.text(0, 20, "END", 1);
  myOLED.display();
}

void loop() {
  // empty loop
}
