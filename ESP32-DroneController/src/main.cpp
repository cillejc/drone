#include <Arduino.h>
#include <string.h>
#include <drone.h>
#include <joystick.h>
#include <FlipButton.h>

String ssid = "flexlab2";
String password = "flexiwifi";

Drone drone(ssid, password);
Joystick joystick(15, 34, 35); // pins: btn, x, y
FlipButton flip_button(12);

void setup()
{
  Serial.begin(9600);

  drone.joystick = &joystick; 

  for (size_t i = 0; i < 5; i++)
  {
    Serial.println(i);
    delay(1000);
  }

  joystick.addButtonListener(&drone);
  flip_button.addButtonListener(&drone);
  
  drone.connect();
  drone.setIp ("192.168.1.146");
}

void loop()
{
  joystick.loop();
  flip_button.loop();
  drone.loop();;
}