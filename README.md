# NUCLEO-L432KC Firmware – Flex and Gyroscope Output

This firmware is written in C++ using Mbed OS for the NUCLEO-L432KC microcontroller. It outputs a total of **8 data points** over I2C:

- **5 Flex Sensor readings** (one for each finger)  
- **3 Gyroscope readings** in degrees per second: **roll**, **pitch**, and **yaw**

The data stream is intended to be consumed by an external system via I2C. A separate Python script using `asyncio.open_connection` is used to asynchronously read and process the incoming sensor values.
