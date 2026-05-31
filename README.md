# DC Motor Speed Control using PID and Encoder Feedback

This repository contains an Arduino-based PID speed control project for a DC motor with encoder feedback. The controller measures the motor speed using an encoder, compares it with a desired target speed, and adjusts the PWM signal using a PID control algorithm.

The main objective is to keep the motor rotating at a desired speed in RPM despite load changes or disturbances.

---

## Project Overview

In this project, a DC motor is controlled using:

- Arduino
- Motor driver
- Encoder feedback
- PWM speed control
- PID controller

The encoder measures the motor rotation. The Arduino calculates the motor speed in RPM and applies a PID controller to adjust the PWM duty cycle.

The motor speed is controlled around the target value:

```text
setpoint = 100 RPM
