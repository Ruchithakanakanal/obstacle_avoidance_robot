#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Ultrasonic Sensor Pins and Constants
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

// Motor Speed Constants
#define MAX_SPEED 150 // Sets max speed of DC motors
#define MAX_SPEED_OFFSET 20

// Initialize ultrasonic sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Initialize motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Initialize servo motor
Servo myservo;

// Global variables
boolean goesForward = false;
int distance = 100;
int speedSet = MAX_SPEED;

void setup() {
    myservo.attach(10);
    myservo.write(115);
    delay(2000);
    
    // Read initial distance values
    for (int i = 0; i < 4; i++) {
        distance = readPing();
        delay(100);
    }
}

void loop() {
    int distanceR = 0;
    int distanceL = 0;
    delay(40);

    if (distance <= 15) {
        moveStop();
        delay(100);
        moveBackward();
        delay(300);
        moveStop();
        delay(200);
        
        distanceR = lookRight();
        delay(200);
        distanceL = lookLeft();
        delay(200);

        if (distanceR >= distanceL) {
            turnRight();
        } else {
            turnLeft();
        }
        moveStop();
    } else {
        moveForward();
        adjustSpeed();
    }
    distance = readPing();
}

int lookRight() {
    myservo.write(50);
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);
    return distance;
}

int lookLeft() {
    myservo.write(170);
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);
    return distance;
}

int readPing() {
    delay(70);
    int cm = sonar.ping_cm();
    return (cm == 0) ? 250 : cm;
}

void moveStop() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void moveForward() {
    if (!goesForward) {
        goesForward = true;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
            motor1.setSpeed(speedSet);
            motor2.setSpeed(speedSet);
            motor3.setSpeed(speedSet);
            motor4.setSpeed(speedSet);
            delay(5);
        }
    }
}

void moveBackward() {
    goesForward = false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
        motor1.setSpeed(speedSet);
        motor2.setSpeed(speedSet);
        motor3.setSpeed(speedSet);
        motor4.setSpeed(speedSet);
        delay(5);
    }
}

void turnRight() {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(500);
    moveForward();
}

void turnLeft() {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(500);
    moveForward();
}

void adjustSpeed() {
    int distance = readPing();
    speedSet = MAX_SPEED + map(distance, 15, 100, MAX_SPEED_OFFSET, 0);
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
}
