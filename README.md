# NUCLEO-L432KC Firmware – Flex and Gyroscope Output

This firmware is written in C++ using Mbed OS for the NUCLEO-L432KC microcontroller. It outputs a total of **8 data points** over I2C:

- **5 Flex Sensor readings** (one for each finger)  
- **3 Gyroscope readings** in degrees per second: **roll**, **pitch**, and **yaw**

## Sensors Used

- **BNO055** – Intelligent 9-axis absolute orientation sensor  
  Used for capturing orientation data (gyroscope: roll, pitch, yaw).

- **Spectra Symbol Flex Sensors** – One per finger  
  Thin bend sensors that vary resistance based on curvature. Approx. 10kΩ flat; up to 110kΩ when bent.

## Communication

The sensor data is transmitted over I2C and can be read using a Python script via `asyncio.open_connection`.

---
<img width="130" height="200" alt="image" src="https://github.com/user-attachments/assets/3b244160-9f7c-40ed-8136-1fb56596861f" />
<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/0689eabf-8bba-4c67-98a1-dd9b39634cd5" />
<img width="275" height="200" alt="image" src="https://github.com/user-attachments/assets/590d12fe-3d05-4eb0-8075-ac86a7095ed5" />
<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/f02972db-56c1-4695-ab95-a5db161ddffb" />

---
