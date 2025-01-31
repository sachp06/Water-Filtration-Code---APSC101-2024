# Water Filtration System Code

## Overview

This repository contains the code for a water filtration system that automates and monitors the filtration process. The system uses motors, pumps, sensors, and a servo for water flow control, monitoring, and interaction. The system includes functionalities for:
- Starting and stopping a centrifugal pump.
- Monitoring water levels via a capacitive sensor.
- Controlling a DC motor and servo based on the filtration process.
- Manual override with an emergency stop button.

## Features

- **Automated Pump Control:** Start and stop the centrifugal and peristaltic pumps based on sensor input.
- **Water Level Detection:** Use a capacitive sensor to detect the presence of an object (e.g., a water level) near the sensor.
- **Motor and Servo Control:** Control a DC motor and servo for the mechanical parts of the filtration system.
- **Manual Override:** A button (Estop) allows for a manual emergency stop that halts all motors.
- **Data Logging:** Print sensor readings to the serial monitor for debugging and monitoring purposes.

## Requirements

- **Hardware:**
  - Arduino (or compatible microcontroller)
  - DC motor (connected to M2)
  - Peristaltic pump (connected to M4)
  - Centrifugal pump (connected to M2)
  - Servo motor (connected to pin 9)
  - Capacitive sensor (connected to pin 52)
  - Pushbutton (connected to pin A2)
  - Emergency stop button (connected to pin 21)

- **Libraries:**
  - `AFMotor.h` for motor control (for DC and pump motors)
  - `Servo.h` for controlling the servo motor

## Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/your-username/water-filtration-system.git
