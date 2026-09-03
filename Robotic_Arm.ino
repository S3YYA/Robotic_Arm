#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_PWMServoDriver.h>

// MPU6050 and PCA9685 objects
Adafruit_MPU6050 mpu;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // I2C default address 0x40

// Servo channel assignments
#define SERVO_X_CHANNEL     0
#define SERVO_Y_CHANNEL     1
#define SERVO_TOUCH_CHANNEL 2

// Capacitive touch sensor
const int touchPin = T5;         // GPIO 12 (Touch pin)
const int touchThreshold = 30;   // You may need to tune this based on your sensor

// Servo pulse parameters
#define SERVO_MIN_PULSE  500     // microseconds
#define SERVO_MAX_PULSE  2500    // microseconds
#define SERVO_FREQ       50      // Hz

// Convert angle (0-180) to PCA9685 pulse
uint16_t angleToPulse(int angle) {
  int pulseLength = map(angle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  return (uint16_t)(pulseLength * 4096 / 20000);  // Convert to PCA9685 scale
}

void setup() {
  Serial.begin(115200);

  // Initialize I2C with custom SDA/SCL for ESP32
  Wire.begin(21, 22);  // SDA = GPIO 21, SCL = GPIO 22

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  Serial.println("MPU6050 initialized");

  // Initialize PCA9685 servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  // Set initial servo positions
  pwm.setPWM(SERVO_X_CHANNEL, 0, angleToPulse(0));
  pwm.setPWM(SERVO_Y_CHANNEL, 0, angleToPulse(0));
  pwm.setPWM(SERVO_TOUCH_CHANNEL, 0, angleToPulse(70));
}

void loop() {
  // Read sensor data from MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Map gyro values to servo angles (scaled down)
  int angleX = map((int)(g.gyro.x * 1000), -30000, 30000, 0, 70);
  int angleY = map((int)(g.gyro.y * 1000), -30000, 30000, 0, 70);
  angleX = constrain(angleX, 0, 70);
  angleY = constrain(angleY, 0, 70);

  // Update servo positions
  pwm.setPWM(SERVO_X_CHANNEL, 0, angleToPulse(angleX));
  pwm.setPWM(SERVO_Y_CHANNEL, 0, angleToPulse(angleY));

  // Read capacitive touch sensor
  int touchValue = touchRead(touchPin);
  int touchAngle = (touchValue < touchThreshold) ? 0 : 70;
  pwm.setPWM(SERVO_TOUCH_CHANNEL, 0, angleToPulse(touchAngle));

  // Debug output to Serial Monitor
  Serial.print("Servo X (Gyro X): ");
  Serial.print(angleX);
  Serial.print("°\t");

  Serial.print("Servo Y (Gyro Y): ");
  Serial.print(angleY);
  Serial.print("°\t");

  Serial.print("Touch Value: ");
  Serial.print(touchValue);
  Serial.print("\t");

  Serial.print("Servo Touch: ");
  Serial.print(touchAngle);
  Serial.println("°");

  delay(100);
}
