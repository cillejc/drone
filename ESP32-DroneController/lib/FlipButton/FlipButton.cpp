#include <Arduino.h>
#include <FlipButton.h>

FlipButton::FlipButton(int pinBtn)
{
    this->pinBtn = pinBtn;
    pinMode (this->pinBtn, INPUT);
}

void FlipButton::addButtonListener(FlipButtonListener *btnLsn)
{
    this->flipButtonListener = btnLsn; 
    this->listenerIsSet = true;
    Serial.println("[INFO] Done setting listener");
}

void FlipButton::loop()
{
    // If joystick btn is pressed and not already set as pressed
    if (digitalRead(this->pinBtn) == LOW && this->buttonIsPressed == false)
    {
        this->buttonIsPressed = true;
        
        if (this->listenerIsSet)
        {
            this->flipButtonListener->FlipButtonPressed();
        }
    }
    else if (digitalRead(this->pinBtn) == HIGH && this->buttonIsPressed == true)
    {
        this->buttonIsPressed = false;
    }
}