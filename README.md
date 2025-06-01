# CAN-based Automotive Dashboard

## 📌 Project Overview

This project implements a real-time **automotive dashboard system** using the **PIC18F4580** microcontroller, leveraging its built-in **Controller Area Network (CAN)** module. It mimics how modern vehicles use CAN communication for centralized monitoring by receiving data from multiple ECUs (Electronic Control Units) and displaying key vehicle parameters in real time.

## 🔧 Features

- Real-time display of:
  - 🚗 Vehicle speed  
  - 🌡️ Engine temperature  
  - 🔁 RPM  
  - ⚙️ Gear position  
  - 💡 Indicator status (left/right)
- CAN message decoding and live data update
- Modular and scalable architecture
- Educational use of **embedded C programming** and **CAN protocol**

## 🛠️ Technologies Used

- **Microcontroller:** PIC18F4580  
- **Development Board:** RhydoLabz PIC Development Board  
- **Language:** Embedded C  
- **IDE:** MPLAB IDE  
- **Communication Protocol:** CAN (Controller Area Network)

## ⚙️ System Architecture

1. **ECUs** send various sensor data over the CAN bus.
2. **PIC18F4580** with its built-in CAN module receives and decodes the messages.
3. The decoded data is processed and sent to a display module (LCD/LED).
4. The dashboard updates live based on incoming CAN messages.

## 📁 Project Structure

CAN-Dashboard/
├── src/ # Embedded C source files
├── can_config/ # CAN bit timing, filters, masks
├── display_module/ # LCD/LED driver code
├── docs/ # Block diagram, circuit schematic
├── README.md # Project description
└── .hex # Compiled HEX file for flashing


## 🔌 Hardware Requirements

- PIC18F4580 Microcontroller  
- RhydoLabz CAN-enabled development board  
- CAN transceiver (e.g., MCP2551)  
- Display module (e.g., 16x2 LCD or 7-segment display)  
- External ECUs or simulated CAN data sources  
- Power supply (5V regulated)

## 🚀 Getting Started

1. Clone or download the repository.
2. Open the project in **MPLAB IDE**.
3. Connect the PIC18F4580 development board and CAN transceiver circuit.
4. Flash the `.hex` file to the microcontroller.
5. Run the setup and observe real-time dashboard updates based on incoming CAN messages.

## 📚 Learning Outcomes

- Hands-on experience with **CAN protocol**
- Understanding of **real-time data handling**
- Embedded system development using **PIC microcontrollers**
- Working with **sensor data** and **interfacing modules**
