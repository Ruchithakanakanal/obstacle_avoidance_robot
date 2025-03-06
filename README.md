# obstacle_avoidance_robot

An autonomous robot that uses an ultrasonic sensor to detect obstacles and navigate around them. It moves forward, avoids obstacles, and turns based on available space.

## Features:
- Ultrasonic sensor (HC-SR04) for obstacle detection.
- Servo motor to scan left and right.
- DC motors for movement (forward, backward, turn left/right).
- Speed adjustment based on distance.

## Hardware:
-**Arduino Uno** (or compatible)
- *L293D Motor Driver Shield*  
- *Ultrasonic Sensor (HC-SR04)*  
- *4 Gear Motors*  
- *Battery Switch*  
- **Servo Motor**
- **DC Motors with Motor Driver (AFMotor)**

## Software:
- Arduino IDE
- Libraries:
  - `AFMotor` (for DC motors)
  - `NewPing` (for ultrasonic sensor)
  - `Servo` (for servo control)

## How to Use:
1. **Wiring**: 
   - TRIG_PIN: A0, ECHO_PIN: A1
   - Motors: Pins 1-4
   - Servo: Pin 10
2. **Upload Code**: Open the Arduino IDE, upload the code to your board.
3. **Power On**: The robot will start moving, avoid obstacles, and turn accordingly.

## License:
MIT License. See [LICENSE](LICENSE).

## Contributions:
Feel free to fork and submit pull requests!
