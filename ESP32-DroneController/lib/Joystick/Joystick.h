// These are "include guards".
// If multiple classes are called joystick, then it 
// might be imported mulitple times. This make sure
// this doesn't happen.
#ifndef A812D987_C035_417F_B3E8_E665B02237A4
#define A812D987_C035_417F_B3E8_E665B02237A4

#include <Arduino.h>
#include <Position.h>
#include <ButtonListener.h>

class Joystick 
{
    public:
        Joystick(int pinBtn, int pinX, int pinY);
        Position getPosition();
        void loop();
        void addButtonListener(ButtonListener *btnLsn);
        int getX();
        int getY();
        bool isBtnPressed();
    private:
        int deadZone = 256;
        Position position;
        int pinBtn;
        int pinX;
        int pinY;
        int y;
        int x;
        bool listenerIsSet = false;
        ButtonListener *buttonListener;
        bool buttonIsPressed = false;
};

#endif /* A812D987_C035_417F_B3E8_E665B02237A4 */
