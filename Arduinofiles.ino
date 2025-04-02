/*
 * TB6612 Motor Controller for Smart Robot Car
 * Receives motor commands from computer via Serial
 * Controls motors using TB6612 driver
 */

// TB6612 Motor driver pins
#define PIN_Motor_STBY 3
#define PIN_Motor_PWMA 5  // Controls motor A speed via PWM
#define PIN_Motor_PWMB 6  // Controls motor B speed via PWM
#define PIN_Motor_AIN_1 7 // Controls motor A direction
#define PIN_Motor_BIN_1 8 // Controls motor B direction

// Motor direction definitions
#define direction_forward true
#define direction_backward false

// Variables to store motor values
int16_t leftMotor = 0;
int16_t rightMotor = 0;
uint8_t frameNumber = 0;

void setup() {
  // Initialize serial communication with correct baud rate
  Serial.begin(57600);

  // Configure motor control pins
  pinMode(PIN_Motor_STBY, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  
  // Enable the motor driver
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  // Initialize motors to stopped state
  motorControl(direction_forward, 0, direction_forward, 0);
}

void loop() {
  // Check for incoming serial data
  if (Serial.available() >= 4) { // We expect 4 bytes (2 int16_t values)
    // Read left and right motor values
    byte buffer[4];
    Serial.readBytes(buffer, 4);
    
    // Convert bytes to int16_t values
    leftMotor = (buffer[1] << 8) | buffer[0];   // Little endian
    rightMotor = (buffer[3] << 8) | buffer[2];  // Little endian
    
    // Apply motor controls
    applyMotorValues(leftMotor, rightMotor);
    
    // Send data back to computer (for debugging/feedback)
    sendMotorValues();
  }
}

// Apply motor values received from computer
void applyMotorValues(int16_t left, int16_t right) {
  // Determine direction for each motor
  boolean leftDirection = direction_forward;
  boolean rightDirection = direction_forward;
  
  // Convert received values to appropriate ranges (0-255)
  uint8_t leftSpeed = min(255, abs(left));
  uint8_t rightSpeed = min(255, abs(right));
  
  // If speed is negative, change direction
  if (left < 0) {
    leftDirection = direction_backward;
  }
  
  if (right < 0) {
    rightDirection = direction_backward;
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
  int16_t values[2] = {leftMotor, rightMotor};
  Serial.write((uint8_t*)values, 4);  // Send 4 bytes (2 int16_t values)
  frameNumber++;
}
