#include <Wire.h>
#include "RTClib.h"

#include <LiquidCrystal.h>

// Motor
const int ENABLE = 5;
const int DIRA = 3;
const int DIRB = 4;

const char* FAN_STRS[4] = {"   0", " 1/2", " 3/4", "Full"};
const int FAN_SPEEDS[4] = {0, 127, 192, 255};  // 0%, 50%, 75%, 100%
bool speed_up = true;
int speed_index = 0;

// Button
const int BUTTON = 2;   // only 2, 3, 18, 19, 20, 21
volatile bool state = HIGH;

// LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Clock
RTC_Millis rtc;


void update_display() {
    DateTime now = rtc.now();
    lcd.setCursor(0, 0);
    lcd.print("Time:");
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    lcd.print(":");
    lcd.print(now.second());
    lcd.print(" ");
    // Motor info
    lcd.setCursor(0, 1);
    if (state) {
      lcd.print("C ");
    } 
    else {
      lcd.print("CC");
     }
    lcd.print(" Speed:");

    //lcd.setCursor(12, 1);
    lcd.print(FAN_STRS[speed_index]);
}

void set_speed(const int speed) {

    // Set the new speed
    analogWrite(ENABLE, speed);

    // Update directions
    digitalWrite(DIRA, state);
    digitalWrite(DIRB, !state);
}

void setup() {
    Serial.begin(9600);
    rtc.begin(DateTime((__DATE__), (__TIME__)));

    pinMode(ENABLE, OUTPUT);
    pinMode(DIRA, OUTPUT);
    pinMode(DIRB, OUTPUT);

    // Motor
    digitalWrite(DIRA, state);
    digitalWrite(DIRB, !state);
    analogWrite(ENABLE, 127);

    // Button
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), button_interupt, RISING);

    // LCD
    lcd.begin(16, 2);

}

void loop() {

    // Speed up/down
    if (speed_index == 3) {
        speed_up = false;
    } else if (speed_index == 0) {
        speed_up = true;
    }

    speed_index += (speed_up ? 1 : -1);
    set_speed(FAN_SPEEDS[speed_index]);


    // Update the LCD
    update_display();

    delay(1000);
}

void button_interupt() {
    state = !state;
}