# SP-INNOVATORS

## IoT and Robotics-Based Sewage Manhole and Pipeline Cleaning Robot

An IoT and robotics-based system designed for inspection, cleaning, and maintenance of sewage manholes and underground pipelines.

## 📌 Project Overview

Sewage manholes and underground pipelines require regular inspection and cleaning to prevent blockage, accumulation of waste, and maintenance problems.

The SP-INNOVATORS project proposes a robotic cleaning system that can be remotely controlled to perform cleaning operations while providing real-time visual inspection using an ESP32-CAM.

The system combines robotic movement, cleaning mechanisms, a lead-screw mechanism, wireless communication, and real-time camera monitoring.

## 🎯 Objectives

- Develop a remotely controlled sewage cleaning robot.
- Enable movement inside manholes and pipeline environments.
- Provide a mechanism for cleaning accumulated waste.
- Provide a lead-screw mechanism for controlled mechanical movement.
- Monitor the robot using an ESP32-CAM.
- Provide real-time visual inspection.
- Reduce the need for direct human entry into hazardous sewage environments.
- Develop a low-cost prototype suitable for further research and development.

## ⚙️ Main Features

- 🚜 Tracked robotic movement
- 🧹 Cleaning mechanism
- ⚙️ Lead-screw mechanism
- 📡 Esp-now Wireless transmitter and receiver communication
- 📷 ESP32-CAM real-time inspection
- 🛑 Limit-switch protection
- 🔧 ESP32-based control system

## 🧠 System Architecture

```text
                    CONTROL SYSTEM
                         │
                         ▼
              PCL TRANSMITTER ESP32
                         │
                  Wireless Link
                         │
                         ▼
               PCL RECEIVER ESP32
                         │
          ┌──────────────┼──────────────┐
          ▼              ▼              ▼
     Track Motors   Cleaning Motor   Lead-Screw
          │              │              │
          └──────────────┼──────────────┘
                         │
                         ▼
                   Cleaning Robot

                         │
                         ▼
                    ESP32-CAM
                         │
                         ▼
                Real-Time Inspection
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
