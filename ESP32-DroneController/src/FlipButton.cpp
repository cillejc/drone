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
    Serial.println("done setting listener");
}

void FlipButton::loop()
{
    //Serial.println(digitalRead(this->pinBtn));
    // if joystick btn is pressed and not already set as pressed
    if (digitalRead(this->pinBtn) == LOW && this->buttonIsPressed == false)
    {
        this->buttonIsPressed = true;

        Serial.println("HIT");
        
        if (this->listenerIsSet)
        {
            Serial.println("HIT 2");
            this->flipButtonListener->FlipButtonPressed();
        }
    }
    else if (digitalRead(this->pinBtn) == HIGH && this->buttonIsPressed == true)
    {
        Serial.println("HIT3");
        this->buttonIsPressed = false;
    }

}