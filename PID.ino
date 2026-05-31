// Encoder
volatile long encoderCount = 0;
unsigned long lastTime = 0;
long lastEncoderCount = 0;

// Motor
const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

// PID Gains (Tune these)
float Kp = 0.5;
float Ki = 0.1;
float Kd = 0.01;

float integral = 0;
float prevError = 0;

float setpoint = 100.0; // target speed in RPM

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), encoderISR, RISING);

  // Motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  lastTime = millis();
}

void loop() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;  // Convert ms to seconds

  // Calculate speed from encoder
  noInterrupts();
  long count = encoderCount;
  interrupts();

  float deltaCount = count - lastEncoderCount;
  float speed = (deltaCount / 600.0) * 60.0 / dt;  // RPM (600 CPR)
  lastEncoderCount = count;

  // PID calculations
  float error = setpoint - speed;
  integral += error * dt;
  float derivative = (error - prevError) / dt;

  float output = Kp * error + Ki * integral + Kd * derivative;
  prevError = error;

  // PWM limit and apply
  int pwm = constrain(output, 0, 255);
  analogWrite(ENA, pwm);

  // Print
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(" RPM\tPWM: ");
  Serial.println(pwm);

  lastTime = now;
  delay(10);  // loop every ~10ms
}

void encoderISR() {
  encoderCount++;
}
