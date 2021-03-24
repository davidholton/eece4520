#include <Wire.h>

const unsigned JOY_X = A0; // analog
const unsigned JOY_Y = A1; // analog

const unsigned BUZZER_PIN = A7;
const unsigned BUZZ_TIME = 1000; // How long the buzzer is on in ms
long buzzer_timer = 0; // Current time left

unsigned long previous_time;

void setup() {

    Serial.begin(9600);

    // Joystick
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);

    // Gyro sensor
    Wire.begin();
    Wire.beginTransmission(0x68);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // Wake up MPU-6050
    Wire.endTransmission(true);

    // Buzzer
    pinMode(BUZZER_PIN, OUTPUT);
    previous_time = millis();

}

void loop() {

    // Timer for how long the buzzer should beep
    unsigned long current_time = millis();
    unsigned long dt = current_time - previous_time;

    // If timer is active decrement by the delta time
    if (buzzer_time > 0) {
        buzzer_time -= dt;
    }

    // If the timer is finished turn off the buzzer
    if (buzzer_time <= 0) {
        digitalWrite(BUZZER_PIN, LOW);
    }

    int x_pos = map(analogRead(JOY_X), 0, 1023, -512, 512);
    int y_pos = map(analogRead(JOY_Y), 0, 1023, -512, 512);

    // MPU-6050 controls
    Wire.beginTransmission(0x68);
    Wire.write(0x43); // Starting with register 0x43 (GYRO_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true); // request a total of 14 registers

    int16_t g_x = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    int16_t g_y = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    int16_t g_z = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    if (Serial.available() > 0) {
        int byte = Serial.read();

        // 'e' means we ate an apple. Turn on buzzer
        if (byte == 'e') {
            buzzer_time = BUZZ_TIME;
            digitalWrite(BUZZER_PIN, HIGH);
        }
    }

    // Use Gyro controls
    x_pos = map(g_x, -32768, 32767, -512, 512);
    y_pos = map(g_y, -32768, 32767, -512, 512);

    Serial.print(x_pos);
    Serial.print(" ");
    Serial.println(y_pos);
    
    previous_time = current_time;
    delay(150);

}
