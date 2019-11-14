#include <Arduino.h>
#include <Joystick.h>

/*
*
*   created by Ebbe Vang, October 2019
*   Remember to reverse v and gnd because of pullup :-)
*
*/

Joystick::Joystick(int pinBtn, int pinX, int pinY)
{
    this->pinBtn = pinBtn;
    this->pinX = pinX;
    this->pinY = pinY;

    pinMode (this->pinBtn, INPUT_PULLUP);
    pinMode (this->pinX, INPUT);
    pinMode (this->pinY, INPUT);
}

void Joystick::addButtonListener(ButtonListener *btnLsn)
{
    this->buttonListener = btnLsn; 
    this->listenerIsSet = true;
    Serial.println("[INFO] Done setting listener");
}

bool Joystick::isBtnPressed()
{
    return this->buttonIsPressed;
}

void Joystick::loop()
{
    // If joystick btn is pressed and not already set as pressed
    if (digitalRead(this->pinBtn) == 0 && this->buttonIsPressed == false)
    {
        this->buttonIsPressed = true;
        
        if (this->listenerIsSet)
        {
            this->buttonListener->ButtonPressed();
        }
    }    
    else if (digitalRead(this->pinBtn) == 1 && this->buttonIsPressed == true)
    {
        this->buttonIsPressed = false;
    }

    this->x = analogRead(this->pinX);
    this->y = analogRead(this->pinY);

    if (x > 2048 + this->deadZone || x < 2048 - this->deadZone)
    {
        this->x = this->x - 2048;
    }
    else this->x=0;
    if (y > 2048 + this->deadZone || y < 2048 - this->deadZone)
    {
        this->y = this->y - 2048;
    }
    else this->y = 0;
}

Position Joystick::getPosition()
{
    this->position = Position(this->x, this->y);
    return this->position;
}

int Joystick::getX()
{
    return this->x;
}

int Joystick::getY()
{
    return this->y;
}