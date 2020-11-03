/**********************************************************************************
 *  Download the libraries:
 *  https://github.com/Aircoookie/Espalexa
 *  
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board:
 *  For ESP8266 NodeMCU (2.5.1): https://github.com/esp8266/Arduino
 *  For ESP32                  : https://github.com/espressif/arduino-esp32
 **********************************************************************************/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
// define the GPIO connected with Relays
#define RelayPin1 5  //D1
#define RelayPin2 4  //D2
#define RelayPin3 13 //D7
#define RelayPin4 14 //D5
#define RelayPin5 12 //D6

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);

// WiFi Credentials
const char* ssid = "WiFi Name";
const char* password = "WiFi Password";

// device names
String Device_1_Name = "Room light";
String Device_2_Name = "Blue bulb";
String Device_3_Name = "Yellow bulb";
String Device_4_Name = "Red bulb";
String Device_5_Name = "CFL bulb";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);
    espalexa.addDevice(Device_5_Name, fifthLightChanged);

    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, HIGH);
      Serial.println("Device1 ON");
    }
  else
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, HIGH);
      Serial.println("Device2 ON");
    }
  else
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, HIGH);
      Serial.println("Device3 ON");
    }
  else
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("Device3 OFF");
  }
}

void fourthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, HIGH);
      Serial.println("Device4 ON");
    }
  else
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("Device4 OFF");
  }
}

void fifthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin5, HIGH);
      Serial.println("Device5 ON");
    }
  else
  {
    digitalWrite(RelayPin5, LOW);
    Serial.println("Device5 OFF");
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
