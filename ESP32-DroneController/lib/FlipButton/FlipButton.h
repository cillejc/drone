#ifndef A812D987_C035_417F_B3E8_E665B02237A4_FLIPPY
#define A812D987_C035_417F_B3E8_E665B02237A4_FLIPPY

#include <Arduino.h>
#include <Position.h>
#include <FlipButtonListener.h>

class FlipButton
{
    public:
        FlipButton(int pinBtn);
        void loop();
        void addButtonListener(FlipButtonListener *btnLsn);
    private:
        int pinBtn;
        bool listenerIsSet = false;
        FlipButtonListener *flipButtonListener;
        bool buttonIsPressed = false;
};

#endif /* A812D987_C035_417F_B3E8_E665B02237A4_FLIPPY */
