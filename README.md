# 🐟 IoT-Based Water Quality Monitoring System for Koi Fish Quarantine Ponds

An Internet of Things (IoT)-based water quality monitoring system designed to assist koi breeders in maintaining optimal water conditions during the quarantine process. The system continuously monitors temperature, pH, turbidity, and Total Dissolved Solids (TDS) in real time using ESP32 and multiple sensors, with data accessible through the Blynk mobile application.

## Features

- Real-time monitoring of water temperature, pH, turbidity, and TDS
- Remote monitoring through the Blynk IoT platform
- Local OLED display for instant parameter visualization
- Automatic heater activation when water temperature falls below the threshold
- Buzzer notifications for abnormal water conditions
- Wi-Fi connectivity using ESP32
- Designed according to koi fish quarantine water quality requirements

## Hardware Components

- ESP32 Development Board
- DS18B20 Temperature Sensor
- pH 4502C Sensor
- Turbidity Sensor SEN0189
- TDS Sensor V1.0
- ADS1115 16-bit ADC Module
- OLED Display (I2C)
- Relay Module
- Water Heater
- Buzzer

## IoT Monitoring Dashboard

The system transmits sensor data to the Blynk platform, allowing users to monitor water quality remotely through smartphones or computers. The dashboard displays:

- Water Temperature (°C)
- pH Level
- Turbidity (NTU)
- Total Dissolved Solids (ppm)

Users receive notifications whenever measured values exceed the recommended range for koi fish quarantine.

## Water Quality Parameters

| Parameter | Recommended Range |
|------------|------------------|
| Temperature | 20 – 30 °C |
| pH | 6.5 – 8.0 |
| Turbidity | ≤ 25 NTU |
| TDS | 200 – 500 ppm |

## System Architecture

```text
DS18B20
pH Sensor
Turbidity Sensor
TDS Sensor
      │
      ▼
    ADS1115
      │
      ▼
     ESP32
 ┌────┴────┐
 ▼         ▼
OLED     Blynk
Display Dashboard
 │
 ▼
Relay & Heater
 │
 ▼
Buzzer Alert
```

## Project Objectives

- Develop an IoT-based water quality monitoring system for koi fish quarantine ponds.
- Monitor critical water quality parameters in real time.
- Improve monitoring efficiency compared to conventional manual methods.
- Assist koi breeders in maintaining optimal water conditions and reducing disease risks.

## Technologies Used

- ESP32
- Arduino IDE
- Blynk IoT
- C++
- I2C Communication
- Wi-Fi Connectivity
- Sensor Integration

## Industry Partner

This project was developed in collaboration with **Dadang Koi**, a koi fish breeding and quarantine facility located in Palembang, Indonesia.

The partner provided:
- Real-world quarantine pond environments for system deployment and testing
- Practical insights into koi fish quarantine procedures
- Water quality monitoring requirements based on daily operational needs
- Feedback for evaluating system functionality and usability

The collaboration ensured that the developed solution addressed actual challenges faced by koi breeders in maintaining water quality during the quarantine process.

## Author

**Putri Nadhiyah Salsabila**

IoT & Full Stack Developer

Politeknik Negeri Sriwijaya
