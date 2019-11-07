#include <Arduino.h>
#include <Position.h>
#include <ButtonListener.h>

class FlipButton
{
    public:
        FlipButton(int pinBtn);
        void loop();
        void addButtonListener(ButtonListener *btnLsn);
    private:
        int pinBtn;
        bool listenerIsSet = false;
        // TODO: change buttonListener to vector of buttonlisteners?
        ButtonListener *buttonListener;
        bool buttonIsPressed = false;
};
