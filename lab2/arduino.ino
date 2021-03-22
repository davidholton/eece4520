// const unsigned SERIAL_MONITOR = 0;

const unsigned BUZZER_PIN = 0;
const unsigned JOY_X = A0; // analog
const unsigned JOY_Y = A1; // analog

const unsigned BUZZ_TIME = 1000; // ms
unsigned int buzzer_time = 0;

unsigned long previous_time;

int x_dir;
int y_dir;

void setup() {
  Serial.begin(9600);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Joystick
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);

  // Gyro sensor

  previous_time = millis();
}

void loop() {
  unsigned long current_time = millis();
  unsigned long dt = previous_time - current_time;

  if (buzzer_time > 0) {
    buzzer_time -= dt;
  }

  if (buzzer_time <= 0) {
    // Turn off the buzzer
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (Serial.available() > 0) {
    int read_byte = Serial.read();
    if (read_byte == 1) {
      buzzer_time = BUZZ_TIME;
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }

  x_dir = map(analogRead(JOY_X), 0, 1023, -512, 512);
  y_dir = map(analogRead(JOY_Y), 0, 1023, -512, 512);

  Serial.print(x_dir);
  Serial.print(" ");
  Serial.print(y_dir);
  Serial.println();

  previous_time = current_time;
}