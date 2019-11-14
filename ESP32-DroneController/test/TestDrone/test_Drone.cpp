/*
Documentation:
https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/unit-tests.html
https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html#tutorial-unit-testing-blink
https://docs.platformio.org/page/plus/unit-testing.html
*/

#include <Arduino.h>
#include <unity.h>
#include <Joystick.h>
#include <Position.h>
#include <Drone.h>

void test_position_init(void)
{
    Position pos = Position(0, 0);
    TEST_ASSERT_EQUAL(0, pos.x);
    TEST_ASSERT_EQUAL(0, pos.y);

    Position pos_big = Position(0xFFFFFF, 0xFFFFFF);
    TEST_ASSERT_EQUAL(0xFFFFFF, pos_big.x);
    TEST_ASSERT_EQUAL(0xFFFFFF, pos_big.y);

    Position pos_implicit = Position();
    TEST_ASSERT_EQUAL(-1, pos_implicit.x);
    TEST_ASSERT_EQUAL(-1, pos_implicit.y);
}

void test_drone_connect(void)
{
    Drone d = Drone("Fake", "WiFi");
    d.connect();
    TEST_ASSERT_FALSE(d.connected);

    // Actual WiFi for our drone.
    Drone d2 = Drone("TELLO-FE3296", "");
    d2.connect();
    TEST_ASSERT_TRUE(d.connected);
}

void test_joystick_init(void)
{
    Joystick(33, 12, 13);
}

void test_joystick_getPosition(void)
{
    Joystick stick = Joystick(33, 12, 13);
    stick.getPosition();
}

void test_joystick_addBtnListener(void)
{
    Joystick stick = Joystick(33, 0, 0);
    Drone d = Drone("Fake", "WiFi");
    stick.addButtonListener(&d);
}

int simStickBtn = 33;
Joystick simStick = Joystick(simStickBtn, 0, 0);

void test_joystick_loopReadBtn(void)
{
    digitalWrite(simStickBtn, LOW);
    TEST_ASSERT_TRUE(simStick.isBtnPressed());
}

void loop()
{
    simStick.loop();
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    
    RUN_TEST(test_joystick_init);
    RUN_TEST(test_joystick_getPosition);
    RUN_TEST(test_joystick_addBtnListener);
    RUN_TEST(test_joystick_loopReadBtn);

    RUN_TEST(test_drone_connect);
    
    RUN_TEST(test_position_init);

    UNITY_END();
}