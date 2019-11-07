#include <Arduino.h>
#include <FlipButton.h>


FlipButton::FlipButton(int pinBtn)
{
    this->pinBtn = pinBtn;
    pinMode (this->pinBtn, INPUT);
   
}

void FlipButton::addButtonListener(ButtonListener *btnLsn)
{
    this->buttonListener = btnLsn; 
    this->listenerIsSet = true;
    Serial.println("done setting listener");
}

void FlipButton ::loop()
{
    //Serial.println(digitalRead(this->pinBtn));
    // if joystick btn is pressed and not already set as pressed
    if (digitalRead(this->pinBtn) == HIGH && this->buttonIsPressed == false)
    {
        this->buttonIsPressed = true;
        
        if (this->listenerIsSet)
        {
            this->buttonListener->ButtonPressed();
        }
    }    
    else if (digitalRead(this->pinBtn) == LOW && this->buttonIsPressed == true)
    {
        this->buttonIsPressed = false;
    }

}