# 6-DOF Robotic Arm 🤖
College Electronics course workshop project 
**6-degree-of-freedom robotic arm** controlled using an ESP32 and motion/control inputs.

This project explores the intersection of **robotics, embedded systems, servo control, sensors.**

## 📌 Project Overview

The goal of this project is to build a 6-DOF robotic arm that can be controlled intuitively using gyroscope to detect gestures.

The system consists of:

* 🤖 6-DOF robotic arm
* ⚙️ Servo motors for joint actuation
* 🧠 ESP32 for control and processing
* 🧭 IMU/gyroscope-based motion sensing
* 🎮 Manual control inputs for testing and calibration

Hardware
Main Components

| Component         | Purpose                    |
| ----------------- | -------------------------- |
| ESP32             | Main controller            |
| Servo motors ×6   | Joint actuation            |
| IMU / Gyroscope   | Motion sensing             |
| nRF24L01          | Wireless communication     |
| Power supply      | Servo and controller power |
| Robotic arm frame | Mechanical structure       |

> **Note:** Servo power should be supplied separately from the ESP32 where required. The grounds of the control electronics and servo supply must be properly referenced.

## 🎯 Degrees of Freedom

The arm currently consists of six controllable joints:

1. Base rotation
2. Shoulder
3. Elbow
4. Wrist rotation
5. Wrist movement
6. End-effector / gripper

The exact joint configuration may change as the mechanical design develops.

## 🧠 Control Approach

The controller inputs are converted into commands for the individual arm joints.

A simplified control pipeline is:

## 🚧 Current Challenges

### 1. Gravity and Servo Position

One of the major problems encountered is that standard servo commands do not necessarily tell the system where the physical joint actually is.

If a joint is commanded to a position but the servo cannot hold the arm's weight:

The arm can therefore sag or fall while the controller still assumes the joint is where it was commanded to be.

This highlights the need for **closed-loop position feedback**.

2. Joint Identification

Another challenge is determining which servo/joint should respond to a particular controller movement.

The system needs a reliable mapping between:

3. Smooth Motion

Directly mapping sensor values to servo angles can result in sudden or jerky movements.

Future versions will investigate:

* Input filtering
* Dead zones
* Rate limiting
* Servo acceleration/deceleration
* Motion interpolation

Future Improvements

* [ ] Add joint position feedback
* [ ] Implement closed-loop control
* [ ] Improve controller-to-joint mapping
* [ ] Implement inverse kinematics
* [ ] Add servo limits and safety constraints
* [ ] Improve motion smoothing
* [ ] Add gripper control
* [ ] Improve wireless control
* [ ] Create calibration routines
* [ ] Add emergency stop functionality

What I'm Learning
 
This project has been an opportunity to explore:

* Embedded systems
* Servo control
* IMUs and sensor processing
* Robotics
* Control systems
* Kinematics
* Wireless communication
* Hardware debugging


## 🚀 Status

**Work in Progress**

The current version focuses on getting the individual components working and establishing reliable control of the arm.

The project will evolve toward a more robust closed-loop robotic system.

---

**Built as part of my Summer Build Series.**

*Learning by building, breaking, debugging, and rebuilding.*