# SP-INNOVATORS

# IoT and Robotics-Based Sewage Manhole and Pipeline Cleaning Robot

An IoT and robotics-based robotic system developed for the **inspection, cleaning, and maintenance of sewage manholes and underground pipelines**.

The system combines a tracked mobile robot, cleaning mechanism, lead-screw mechanism, wireless control, and an ESP32-CAM-based real-time inspection system.

---

## 📌 Project Overview

Sewage manholes and underground pipelines require regular inspection and cleaning to prevent blockage, accumulation of waste, and maintenance problems.

The **SP-INNOVATORS Sewage Manhole and Pipeline Cleaning Robot** is designed as a remotely operated robotic system that can perform cleaning operations while allowing the operator to monitor the working environment through a camera.

The robot consists of:

- Tracked drive system
- Cleaning mechanism
- Lead-screw mechanism
- Wireless transmitter and receiver
- ESP32-based control system
- ESP32-CAM real-time inspection system
- Limit-switch protection

The goal is to develop a compact and remotely operated platform that can assist with sewage infrastructure inspection and cleaning.

---

## 🎯 Project Objectives

- Develop a remotely controlled sewage cleaning robot.
- Enable robotic movement inside sewage/manhole environments.
- Provide a mechanical cleaning mechanism.
- Provide controlled linear movement using a lead-screw mechanism.
- Provide real-time visual inspection using an ESP32-CAM.
- Enable wireless control between the operator and robot.
- Reduce the need for direct human entry into potentially hazardous environments.
- Develop a prototype that can be further improved for underground pipeline applications.

---

## ⭐ Main Features

- 🚜 Tracked robotic movement
- 🧹 Mechanical cleaning mechanism
- ⚙️ Lead-screw mechanism
- 📡 Wireless transmitter and receiver control
- 📷 ESP32-CAM real-time inspection
- 🛑 Limit-switch protection
- 🔧 ESP32-based control
- 📐 CAD-designed robotic structure
- 🔌 Separate transmitter and receiver circuits

---

# 🧠 System Architecture

```text
                    OPERATOR
                       │
                       ▼
              PCL TRANSMITTER ESP32
                       │
                       │ Wireless Communication
                       ▼
               PCL RECEIVER ESP32
                       │
          ┌────────────┼────────────┐
          │            │            │
          ▼            ▼            ▼
     TRACK DRIVE   CLEANING      LEAD-SCREW
       MOTORS       MOTOR         MOTOR
          │            │            │
          └────────────┼────────────┘
                       │
                       ▼
                CLEANING ROBOT
                       │
                       ▼
                  ESP32-CAM
                       │
                       ▼
              REAL-TIME INSPECTION
```
## 🤖 Prototype

![Prototype](./orginal_p_i.jpeg)

![Prototype](./original_p_if.jpeg)

## 📐 CAD Design

### Front View
![CAD Front](./CAD_Design_Front.png)

### Isometric View
![CAD Isometric](./CAD_Design_Iso.png)

### Side View
![CAD Side](./CAD_Design_Side.png)

### Top View
![CAD Top](./CAD_Design_Top.png)

## 🔌 Circuit Diagrams

### PCL Transmitter
![Transmitter Circuit](./circuit_image_tra.png)

### PCL Receiver
![Receiver Circuit](./circuit_image_rece.png)
