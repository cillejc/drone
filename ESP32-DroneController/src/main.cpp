#include <Arduino.h>
#include <string.h>
#include <drone.h>
#include <joystick.h>
#include <FlipButton.h>

//String ssid = "flexlab2";
//String password = "flexiwifi";
// 0TQDG5FEDBX4ZQ
String ssid = "TELLO-FE3296";
String password = "";

Drone drone(ssid, password);
Joystick joystick(15, 34, 35); // pins: btn, x, y
FlipButton flipButton(33);

void setup()
{
  Serial.begin(9600);

  drone.joystick = &joystick;
  drone.flipButton = &flipButton;

  for (size_t i = 0; i < 5; i++)
  {
    Serial.println(i);
    delay(1000);
  }

  flipButton.addButtonListener(&drone);
  joystick.addButtonListener(&drone);
  
  drone.setIp ("192.168.10.1");
  drone.connect();
}

void loop()
{
  joystick.loop();
  flipButton.loop();
  drone.loop();;
}