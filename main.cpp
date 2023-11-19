#include "mbed.h"
#include <cstdio>

// I2C SETUP
#define IMU_ADDRESS (0X28 << 1) // to 8 bit address
#define MAX_FREQ 400000
#define OPR_MODE_ADDRESS 0X3D
// MODE SELECT
#define GYROONLY_MODE 0X03
// TEMPERATURE 
#define TEMP_ADDRESS 0X34
// GYRO
#define GYR_CONFIG_ADDRESS_0 0X0A
#define GYR_CONFIG_ADDRESS_1 0X0B

// GYRO <15:8> <7:0>
#define GYR_DATA_Z_MSB 0X19
#define GYR_DATA_Z_LSB 0X18
#define GYR_DATA_Y_MSB 0X17
#define GYR_DATA_Y_LSB 0X16
#define GYR_DATA_X_MSB 0X15
#define GYR_DATA_X_LSB 0X14

//flex
#define INPUT_V 3.3         // supplied voltage
#define MAX_V 3.3           // max allowed input volate
#define RESISTOR 22000      // resistor value

BufferedSerial pc(USBTX, USBRX, 9600); // usb uart
I2C IMU(I2C_SDA, I2C_SCL);

AnalogIn thumbFlex(A6);
AnalogIn indexFlex(A3);
AnalogIn middleFlex(A2);
AnalogIn ringFlex(A1);
AnalogIn pinkyFlex(A0);

FileHandle *mbed::mbed_override_console(int fd){
    return &pc;
}

float flexResistance (float v){
    return ((RESISTOR*(INPUT_V-v))/(v));
}

void toInt(char left, char right, char axis){
    if( left & 0x80 ){
        char l = ~left;
        char r = ~right;
        printf(" %c: -%i",axis, ((l << 8) | r) + 1);
    }else{
        printf(" %c: %i",axis, ((left << 8) | right));
    }
    printf(" ");
}

// main() runs in its own thread in the OS
int main()
{
    // flex sensor 1
    float thumbV = 0.0;
    int thumbR = 0;

    float indexV = 0.0;
    int indexR = 0;

    float middleV = 0.0;
    int middleR = 0;

    float ringV = 0.0;
    int ringR = 0;

    float pinkyV = 0.0;
    int pinkyR = 0;
    

    // gyro 
    char rx = '\0';
    char tx[2] = {'\0', '\0'};
    char gyroData[6] = {'\0','\0','\0','\0','\0','\0'};
    int gyroX = 0;
    int gyroY = 0;
    int gyroZ = 0;

    IMU.frequency(MAX_FREQ);
    IMU.start();
    thread_sleep_for(650);  // wait for startup

    tx[0] = OPR_MODE_ADDRESS;
    tx[1] = GYROONLY_MODE;

    // set gyro mode
    IMU.write(IMU_ADDRESS,tx,2,false);
    thread_sleep_for(7); // data sheet says 7ms

    while (true) {
        tx[0] = GYR_DATA_X_LSB;
        IMU.write(IMU_ADDRESS, tx, 1, true);
        wait_us(4);
        IMU.read(IMU_ADDRESS, gyroData, 6, false);
        wait_us(4);
        
        gyroX = (gyroData[1] << 8) | gyroData[0];
        gyroY = (gyroData[3] << 8) | gyroData[2];
        gyroZ = (gyroData[5] << 8) | gyroData[4];

    
        indexV = (indexFlex.read() * MAX_V);
        indexR = (int)flexResistance(indexV);

        middleV = (middleFlex.read() * MAX_V);
        middleR = (int)flexResistance(middleV);

        ringV = (ringFlex.read() * MAX_V);
        ringR = (int)flexResistance(ringV);

        pinkyV = (pinkyFlex.read() * MAX_V);
        pinkyR = (int)flexResistance(pinkyV);

        thumbV = (thumbFlex.read() * MAX_V);
        thumbR = (int)flexResistance(thumbV);
        
        printf("X:%5d y:%5d z:%5d F1:%6d F2:%6d F3:%6d F4:%6d F5:%6d \n", gyroX, gyroY, gyroZ, thumbR, indexR, middleR, ringR, pinkyR);
        thread_sleep_for(200);
    }
}

