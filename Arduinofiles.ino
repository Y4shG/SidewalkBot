// TB6612 Motor driver pins
#define PIN_Motor_STBY 3
#define PIN_Motor_PWMA 5  // Controls motor A speed via PWM
#define PIN_Motor_PWMB 6  // Controls motor B speed via PWM
#define PIN_Motor_AIN_1 7 // Controls motor A direction
#define PIN_Motor_BIN_1 8 // Controls motor B direction
#define PIN_STATUS_LED 13 // Status LED

// Motor direction definitions
#define DIRECTION_FORWARD true
#define DIRECTION_BACKWARD false

// Configuration
#define SERIAL_BAUD_RATE 57600
#define COMMAND_TIMEOUT 1000  // Stop motors if no commands received (ms)
#define ACCEL_RATE 5          // Rate of speed change per cycle

// Variables
int16_t leftMotor = 0;
int16_t rightMotor = 0;
int16_t currentLeftMotor = 0;
int16_t currentRightMotor = 0;
uint8_t frameNumber = 0;
unsigned long lastCommandTime = 0;

void setup() {
  // Initialize serial communication with correct baud rate
  Serial.begin(SERIAL_BAUD_RATE);

  // Configure motor control pins
  pinMode(PIN_Motor_STBY, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_STATUS_LED, OUTPUT);
  
  // Enable the motor driver
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  // Initialize motors to stopped state
  motorControl(DIRECTION_FORWARD, 0, DIRECTION_FORWARD, 0);
  
  // Signal ready
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_STATUS_LED, HIGH);
    delay(100);
    digitalWrite(PIN_STATUS_LED, LOW);
    delay(100);
  }
}

void loop() {
  // Check for incoming serial data
  readSerialCommands();
  
  // Implement smooth acceleration/deceleration
  updateMotorSpeeds();
  
  // Check watchdog timer
  checkWatchdog();
  
  // Brief delay
  delay(10);
}

void readSerialCommands() {
  if (Serial.available() >= 4) { // We expect 4 bytes (2 int16_t values)
    // Read left and right motor values
    byte buffer[4];
    Serial.readBytes(buffer, 4);
    
    // Convert bytes to int16_t values
    leftMotor = (buffer[1] << 8) | buffer[0];   // Little endian
    rightMotor = (buffer[3] << 8) | buffer[2];  // Little endian
    
    // Update command time
    lastCommandTime = millis();
    digitalWrite(PIN_STATUS_LED, HIGH);
    
    // Send data back to computer (for debugging/feedback)
    sendMotorValues();
  }
}

void updateMotorSpeeds() {
  // Gradually change current speed to match target
  if (currentLeftMotor < leftMotor) {
    currentLeftMotor = min(leftMotor, currentLeftMotor + ACCEL_RATE);
  } else if (currentLeftMotor > leftMotor) {
    currentLeftMotor = max(leftMotor, currentLeftMotor - ACCEL_RATE);
  }
  
  if (currentRightMotor < rightMotor) {
    currentRightMotor = min(rightMotor, currentRightMotor + ACCEL_RATE);
  } else if (currentRightMotor > rightMotor) {
    currentRightMotor = max(rightMotor, currentRightMotor - ACCEL_RATE);
  }
  
  // Apply motor controls with current values
  applyMotorValues(currentLeftMotor, currentRightMotor);
}

void checkWatchdog() {
  // If no valid commands received recently, stop motors
  if (millis() - lastCommandTime > COMMAND_TIMEOUT) {
    if (leftMotor != 0 || rightMotor != 0) {
      leftMotor = 0;
      rightMotor = 0;
      digitalWrite(PIN_STATUS_LED, LOW);
    }
  }
}

// Apply motor values received from computer
void applyMotorValues(int16_t left, int16_t right) {
  // Determine direction for each motor
  boolean leftDirection = DIRECTION_FORWARD;
  boolean rightDirection = DIRECTION_FORWARD;
  
  // Convert received values to appropriate ranges (0-255)
  uint8_t leftSpeed = min(255, abs(left));
  uint8_t rightSpeed = min(255, abs(right));
  
  // If speed is negative, change direction
  if (left < 0) {
    leftDirection = DIRECTION_BACKWARD;
  }
  
  if (right < 0) {
    rightDirection = DIRECTION_BACKWARD;
  }
  
  // Apply motor control
  motorControl(leftDirection, leftSpeed, rightDirection, rightSpeed);
}

// Control motors directly using TB6612 driver
void motorControl(boolean direction_A, uint8_t speed_A, boolean direction_B, uint8_t speed_B) {
  // Set motor A direction and speed
  digitalWrite(PIN_Motor_AIN_1, direction_A);
  analogWrite(PIN_Motor_PWMA, speed_A);
  
  // Set motor B direction and speed
  digitalWrite(PIN_Motor_BIN_1, direction_B);
  analogWrite(PIN_Motor_PWMB, speed_B);
}

// Send motor values back to computer
void sendMotorValues() {
  int16_t values[2] = {currentLeftMotor, currentRightMotor};
  Serial.write((uint8_t*)values, 4);  // Send 4 bytes (2 int16_t values)
  frameNumber++;
}
