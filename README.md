# Robotuk 
### Arduino-Based Autonomous Obstacle-Avoiding Robot

Robotuk is a small autonomous mobile robot built with Arduino. It uses a touch sensor to control its movement and an ultrasonic sensor to detect obstacles and navigate around them.

## Features

- **Touch Control:** Touch the sensor to start or stop the robot.
- **Obstacle Detection:** Detects obstacles in front of the robot using an ultrasonic sensor.
- **Environment Scanning:** Stops and scans both left and right sides to measure available space.
- **Autonomous Decision-Making:** Compares the measured distances and chooses the direction with more available space.
- **Autonomous Movement:** Turns toward the selected direction and continues moving.

## How It Works

1. Robotuk waits for the touch sensor to be activated.
2. Once touched, it starts moving forward.
3. When an obstacle is detected, it stops.
4. It scans the left and right sides to measure the available distance.
5. It compares both measurements and chooses the direction with more space.
6. It turns in that direction and resumes moving.
7. Touching the sensor again stops the robot.

## Hardware Components

- Arduino board
- Touch sensor
- Ultrasonic distance sensor
- Servo motor
- DC motors
- Motor driver
- 8*16 LED Panel
- Battery/power supply

## Technologies

- C++
- Arduino IDE
- Arduino hardware and sensors

## Purpose

This project was built to explore robotics, sensor integration, motor control, and basic autonomous navigation using Arduino.

## Author

Zoya Shegunts

