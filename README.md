# ArduinoInsulation

A Hillsborough County STEM Fair Project that involves using an Arduino. This repository includes the code and instructions on how to use it.
Video is avaiable at the bottom.
## Hardware Setup
### Materials:
- Arduino UNO R4 <img src="https://github.com/user-attachments/assets/d5f73ee5-256b-4384-9eac-ebf076a82745" width="20">
- 6 DHT22's <img src="https://github.com/user-attachments/assets/5fd5d81b-d7c1-45c4-afa1-6381c91e9727" width="20">
- [Sparkfun Qwiic OLED Display 0.91in](https://www.sparkfun.com/products/24606)
- [Sparkfun Qwiic Button](https://www.sparkfun.com/products/15932)
- Qwiic Cables/Male to Female jumper cables
- Other materials for experiment is in the Research Plan
### How to connect:
1. Connect the display to the Arduino using the Qwiic Connect System.
2. Connect the button to the display using the Qwiic Connect System.
3. When program tells you to connect the DHT22 (for each insulation material), connect + to 5V, out to ANALOG IN A0, and connect - to GND.
## Software Setup:
### Libraries:
You can also find these libraries in the Library Manager tab in the Arduino IDE.
- Arduino Uno R4 Boards (under the Boards Manager tab)
- [Qwiic Button Library](https://github.com/sparkfun/SparkFun_Qwiic_Button_Arduino_Library)
- [Qwiic Display Library](https://github.com/sparkfun/SparkFun_Qwiic_OLED_Arduino_Library)
- [DHT22 Library](https://github.com/dvarrel/DHT22)
### Precautions:
- Install COM ports on Windows for the UNO to show up.
- Use a USB-C data cable. Power-only ones won't work!
- Open the Serial Monitor by going to Tools and click on Serial Monitor! Set the baud rate (right corner) to 115200.
## Instructions:
1. Run the program.
2. Press the button when prompted to on the display after following the steps.
3. Repeat the program by pressing the RESET button on the Arduino.
