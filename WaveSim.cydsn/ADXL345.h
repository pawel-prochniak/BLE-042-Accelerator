/* ========================================
 *
 * Copyright Pawel Prochniak, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
*/

#include <project.h>
#include <stdbool.h>
#include <common.h>

#ifndef ADXL345_H
#define ADXL345_H
    
#define NumAve 10 // Calibration samples
    
// Global data
extern union CharValue xData, yData, zData;


// --- REGISTERS, ADRESSES
    // DEVICE I2C ADDRESS
    #define ADXL345_ADDRESS                 (0x53)
    #define ADXL345_ID                      (0xE5)
    
    // CONTROL REGISTERS
    #define ADXL345_REG_BW_RATE             (0x2C)    // Output baud rate
    #define ADXL345_REG_POWER_CTL           (0x2D)    // Power-saving features control

    // DATA REGISTERS
    #define ADXL345_REG_DEVID               (0x00)    // device ID
    #define ADXL345_OFSX                    (0x1E)    // X-axis offset
    #define ADXL345_OFSY                    (0x1F)    // Y-axis offset
    #define ADXL345_OFSZ                    (0x20)    // Z-axis offset
    #define ADXL345_REG_DATA_FORMAT 	    (0x31) 	  // Data format control
    #define ADXL345_REG_DATAX0              (0x32)    // X-axis data 0
    #define ADXL345_REG_DATAX1              (0x33)    // X-axis data 1
    #define ADXL345_REG_DATAY0              (0x34)    // Y-axis data 0
    #define ADXL345_REG_DATAY1              (0x35)    // Y-axis data 1
    #define ADXL345_REG_DATAZ0              (0x36)    // Z-axis data 0
    #define ADXL345_REG_DATAZ1              (0x37)    // Z-axis data 1
    
   
// --- CONTROL VALUES
typedef enum
{
    ADXL345_DATARATE_3200HZ    = 0b1111,
    ADXL345_DATARATE_1600HZ    = 0b1110,
    ADXL345_DATARATE_800HZ     = 0b1101,
    ADXL345_DATARATE_400HZ     = 0b1100,
    ADXL345_DATARATE_200HZ     = 0b1011,
    ADXL345_DATARATE_100HZ     = 0b1010,
    ADXL345_DATARATE_50HZ      = 0b1001,
    ADXL345_DATARATE_25HZ      = 0b1000,
    ADXL345_DATARATE_12_5HZ    = 0b0111,
    ADXL345_DATARATE_6_25HZ    = 0b0110,
    ADXL345_DATARATE_3_13HZ    = 0b0101,
    ADXL345_DATARATE_1_56HZ    = 0b0100,
    ADXL345_DATARATE_0_78HZ    = 0b0011,
    ADXL345_DATARATE_0_39HZ    = 0b0010,
    ADXL345_DATARATE_0_20HZ    = 0b0001,
    ADXL345_DATARATE_0_10HZ    = 0b0000
} DataRate_t;

typedef enum
{
    ADXL345_RANGE_16G          = 0b11,
    ADXL345_RANGE_8G           = 0b10,
    ADXL345_RANGE_4G           = 0b01,
    ADXL345_RANGE_2G           = 0b00
} Range_t ;

    // Constants to scale acc output
    #define SCALE_FACTOR        (0.0039)
    #define GRAVITY_FACTOR      (9.80665)


// Functions to control accel
void startAccConnection();
uint8 getDeviceId();
void setMeasurementRate(DataRate_t dataRate_t);
DataRate_t getMeasurementRate();
void setRange(Range_t range);
void setFullRange();
Range_t getRange();
void getRawDataX();
void getRawDataY();
void getRawDataZ();
void getSensorData();
void offsetCalibration();
void setXOffset(int8 xOff);
void setYOffset(int8 yOff);
void setZOffset(int8 zOff);
void writeRegister(uint8_t reg, uint8_t cmd);
int8_t readRegister(uint8_t reg);
int16_t readRegister16(uint8_t reg);
void showRange();
void showMeasurementRate();
void showXOffset();
void showYOffset();
void showZOffset();

#endif
/* [] END OF FILE */
