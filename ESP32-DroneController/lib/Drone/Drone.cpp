#include <Arduino.h>
#include <Drone.h>
#include <Joystick.h>
#include <Position.h>

Drone::Drone(String ssid, String password)
{
    this->ssid = ssid;
    this->password = password; 
}

void Drone::connect()
{
    Serial.println("[INFO] Drone begin.");

    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("[ERROR] WiFi Failed.");
        while(1) {
            delay(1000);
        }
    }
    if(udp.listen(udpPort)) {
        this->myIp = WiFi.localIP().toString();
        Serial.print("[INFO] UDP Listening on IP: ");
        Serial.println(WiFi.localIP());

        this->connected = true;
      
        udp.onPacket(
            [this](AsyncUDPPacket packet) -> void
            {
                // Cast packet data to char and make String.
                String command((char*)packet.data());
                command = command.substring(0, packet.length()); 
                command.trim();
                // send string to method
                this->commandResponse(command);
            }
        );
    }
    
    // Prepare drone to recieve commands
    this->sendCommand("command");
}

void Drone::sendCommand(String command)
{
    udpSender.beginPacket(this->droneIp.c_str(), udpPort);
    udpSender.printf(command.c_str());
    udpSender.endPacket();    
}

void Drone::setIp(String ip)
{
    this->droneIp = ip;
}
        
void Drone::commandResponse(String response)
{
    Serial.print("[INFO] Got following response: ");
    Serial.println(response.c_str());
    Serial.print("[INFO] Message length: ");
    Serial.println(response.length());
}

void Drone::ButtonPressed()
{
    if (flying == false)
    {
        this->flying = true;
        Serial.println("[COMMAND] takeoff");
        this->sendCommand("[COMMAND] takeoff");
    }
    else
    {
        Serial.println("[COMMAND] land");
        this->sendCommand("[COMMAND] land");
        this->flying = false;
    }
}

void Drone::FlipButtonPressed()
{
    if (flying == true)
    {
        Serial.println("[COMMAND] flip f");
        this->sendCommand("flip f");
    }
}

void Drone::loop()
{
    // Using Position object to retrieve information
    Position joystickPosition = this->joystick->getPosition();
    
    if (joystickPosition.x != 0)
    {
        if (joystickPosition.y != 0)
        {
            // Forward
            if (joystickPosition.x == -2048)
            {
                this->sendCommand("forward 30");
            }

            // Backward
            if (joystickPosition.x == 2047) 
            {
                this->sendCommand("back 30");
            }
            
            // Left
            if (joystickPosition.y == -2048) 
            {
                this->sendCommand("left 30");
            }
            
            // Right
            if (joystickPosition.y == 2047) 
            {
                this->sendCommand("right 30");
            }

            Serial.print(joystickPosition.x);
            Serial.print(" ");
            Serial.println(joystickPosition.y);
        }
    }
}
