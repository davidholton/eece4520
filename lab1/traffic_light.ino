enum State {PAUSED, RED, YELLOW, GREEN};
State current_state = PAUSED;

// TODO: update pins to the corresponding physical pins
const unsigned RED_LED = 0;
const unsigned YELLOW_LED = 1;
const unsigned GREEN_LED = 2;
const unsigned BUZZER_PIN = 3;
const unsigned BUTTON_PIN = 4 ;  

// sets the led to be the only on led
void display_light(const unsigned led) {
    // turn off all of the leds
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    
    // turn on specific led
    digitalWrite(led, HIGH);
}

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, OUTPUT);
}

void loop() {

    switch (current_state) {
        case PAUSED:
            // Entering PAUSED state
            
            if (digitalRead(BUTTON_PIN) == LOW) {
                current_state = RED;
                break;
            }
            
            digitalWrite(RED_LED, HIGH);
            delay(500);
            digitalWrite(RED_LED, LOW);
            delay(500);
            
            current_state = PAUSED;            
            break;
        case RED:
            // Entering RED state
            
            display_light(RED_LED);
            delay(12000);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(3000);
            digitalWrite(BUZZER_PIN, LOW);
            
            current_state = YELLOW;
            break;
        case YELLOW:
            // Entering YELLOW state
            
            display_light(YELLOW_LED);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(3000);
            digitalWrite(BUZZER_PIN, LOW);
            
            current_state = GREEN;
            break;
        case GREEN:
            // Entering GREEN state
            
            display_light(GREEN_LED);
            delay(12000);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(3000);
            digitalWrite(BUZZER_PIN, LOW);
            
            current_state = RED;
            break;
    }

}
