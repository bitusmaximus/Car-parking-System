# 🚗 Car Parking System using ATmega32

A simple embedded car parking management system designed using ATmega32,
simulated in Proteus 8. The system controls entry/exit gates using a servo motor
and displays available slots on a 16x2 LCD.

## 🔧 Features
- Entry and Exit control using push buttons / IR sensors
- Servo motor based gate control
- Real-time slot counting
- Parking full / exit invalid detection
- Proteus 8 simulation

## 🧠 Microcontroller
- ATmega32 @ 16 MHz

## 📌 Pin Configuration
| Component | Pin |
|---------|----|
| Entry Button | PD0 |
| Exit Button | PD1 |
| Servo | PD5 (OC1A) |
| LCD RS | PC0 |
| LCD EN | PC1 |
| LCD D4–D7 | PC4–PC7 |

## 🛠 Tools Used
- Microchip Studio
- Proteus 8 Professional
- AVR-GCC

## ▶ How to Run
1. Open Proteus project
2. Load hex file into ATmega32
3. Run simulation
4. Press buttons to simulate car entry/exit

## 📷 Simulation
![Simulation](proteus/screenshots/simulation.png)
