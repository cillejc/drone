#ifndef C8C7268F_7308_4565_BA1F_FDBA5EBBD88F
#define C8C7268F_7308_4565_BA1F_FDBA5EBBD88F

#include <Arduino.h>
#include <string.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <ButtonListener.h>
#include <FlipButtonListener.h>
#include <Joystick.h>
#include <FlipButton.h>

using namespace std;

class Drone : public ButtonListener, public FlipButtonListener
{
    public:
        Drone(String ssid , String password);
        void connect();
        void sendCommand(String commmand);
        void setIp(String ip);
        String myIp;
        bool connected = false;
        void ButtonPressed();
        void FlipButtonPressed();
        void loop();
        Joystick *joystick;
        FlipButton *flipButton;
    private:
        void commandResponse(String response);
        String ssid;
        String password;
        AsyncUDP udp;
        WiFiUDP udpSender;
        const int udpPort = 8889; 
        String droneIp = "192.168.1.146";
        bool flying = false;
};

#endif /* C8C7268F_7308_4565_BA1F_FDBA5EBBD88F */
