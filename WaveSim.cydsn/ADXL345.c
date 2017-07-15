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
#include <ADXL345.h>
#include <common.h>

int16_t rawDataX, rawDataY, rawDataZ;

union SomeUnion 
{
    float32 fl;
    char ch[4];
    uint8 u[4];
} someUnion;

void startAccConnection() 
{      
    CyDelay(50); // wait for initialization
    uint8 deviceId = getDeviceId();
    printf("Device ID: %x", deviceId);
    writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    
    offsetCalibration();
    
    getSensorData();
    
    printf("\r\nInitial settings");
    showRange();
    showMeasurementRate();

    setRange(ADXL345_RANGE_16G);
    setMeasurementRate(ADXL345_DATARATE_800HZ);
   
    printf("\r\n\nNew settings");
    showRange();
    showMeasurementRate();

    printf("\r\n\nStarted measurement mode\r\n");
}

uint8 getDeviceId() 
{    
    return readRegister(ADXL345_REG_DEVID);
}

void getRawDataX() 
{
    rawDataX = readRegister16(ADXL345_REG_DATAX0);
}

void getRawDataY() 
{
    rawDataY = readRegister16(ADXL345_REG_DATAY0);
}

void getRawDataZ() 
{
    rawDataZ = readRegister16(ADXL345_REG_DATAZ0);
}

void scaleAccValues()
{
    xData.floatVal = (float) (rawDataX * SCALE_FACTOR * GRAVITY_FACTOR);
    yData.floatVal = (float) (rawDataY * SCALE_FACTOR * GRAVITY_FACTOR);
    zData.floatVal = (float) (rawDataZ * SCALE_FACTOR * GRAVITY_FACTOR);
    
    /*
    printf("\r\nRaw X: %d Scaled X float: %f", rawDataX, xData.floatVal);
    printf("\r\nRaw Y: %d Scaled Y float: %f", rawDataY, yData.floatVal);
    printf("\r\nRaw Z: %d Scaled Z float: %f\n", rawDataZ, zData.floatVal);
      */
}

void setMeasurementRate(DataRate_t range) 
{
    writeRegister(ADXL345_REG_BW_RATE, range);
}

DataRate_t getMeasurementRate() 
{
    return (DataRate_t) (readRegister(ADXL345_REG_BW_RATE));
}

void setFullRange() {
    writeRegister(ADXL345_REG_DATA_FORMAT, 0x0B);
}

void setRange(Range_t range) 
{
    uint8 value = getRange();
    
    value &= 0xF0;
    value |= range;
    value |= 0x08; // Full range scaling
    
    writeRegister(ADXL345_REG_DATA_FORMAT, value);
}

Range_t getRange() 
{
    return (Range_t) (readRegister(ADXL345_REG_DATA_FORMAT) & 0x03);
}

void getSensorData() 
{
    getRawDataX();
    getRawDataY();
    getRawDataZ();
    
    scaleAccValues();
}

void clearOffset()
{
    setXOffset(0);
    setYOffset(0);
    setZOffset(0);
}

void offsetCalibration()
{
    printf("\r\n\n-- Starting calibration --\n");
    int8_t average = 0;
    uint8 i = NumAve;
    int8_t aveX, aveY, aveZ;
    
    clearOffset();
    
    getSensorData();
    
    // Sensor should be placed in X=0g, Y=0g, Z=-1g orientation
    CyDelay(10);
    setMeasurementRate(ADXL345_DATARATE_100HZ);
    CyDelay(10);
    showMeasurementRate();
    setRange(ADXL345_RANGE_16G);
    CyDelay(10);
    
    while (i--)
    {
        getRawDataX();
        average += rawDataX;
        CyDelay(1);
    }
    aveX = average / NumAve;
    
    average = 0;
    i = NumAve;
    while (i--)
    {
        getRawDataY();
        average += rawDataY;
        CyDelay(1);
    }
    aveY = average / NumAve;
    
    average = 0;
    i = NumAve;
    while (i--)
    {
        getRawDataZ();
        average += rawDataZ;
        CyDelay(1);
    }
    aveZ = average / NumAve;
    
    int8 offsetX, offsetY, offsetZ;
    
    printf("\r\nAverage X: %d", aveX);
    printf("\r\nAverage Y: %d", aveY);
    printf("\r\nAverage Z: %d", aveZ);
    
    // each LSB of offset is worth 4x LSB in output
    offsetX = (aveX / 4.0);
    offsetY = (aveY / 4.0);
    offsetZ = ((aveZ ) / 4.0 ) ;
    
    setXOffset(offsetX);
    setYOffset(offsetY);
    setZOffset(offsetZ);
    
    showXOffset();
    showYOffset();
    showZOffset();
    printf("\r\n-- Calibration ended --\n");
}

void setXOffset(int8 xOff)
{
    writeRegister(ADXL345_OFSX, xOff);
}

void setYOffset(int8 yOff)
{
    writeRegister(ADXL345_OFSY, yOff);
}

void setZOffset(int8 zOff)
{
    writeRegister(ADXL345_OFSZ, zOff);
}

void showXOffset()
{
    int8_t offset = readRegister(ADXL345_OFSX);
    printf("\r\nX Offset: %d", offset);
}

void showYOffset()
{
    int8_t offset = readRegister(ADXL345_OFSY);
    printf("\r\nY Offset: %d", offset);
}

void showZOffset()
{
    int8_t offset = readRegister(ADXL345_OFSZ);
    printf("\r\nZ Offset: %d", offset);
}

int8_t readRegister(uint8_t reg)
{
    static uint8 readBuffer[0x01];
    uint8 status = I2C_I2CMasterWriteBuf(ADXL345_ADDRESS, &reg, sizeof(reg), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nWrite operation in readRegister ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterReadBuf(ADXL345_ADDRESS, (uint8 *) readBuffer, sizeof(readBuffer), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nRead operation in readRegister ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
    I2C_I2CMasterClearStatus();
    return readBuffer[0x00];
}

int16_t readRegister16(uint8_t reg) 
{
    static uint8 readBuffer[0x02];
    uint8 status = I2C_I2CMasterWriteBuf(ADXL345_ADDRESS, &reg, sizeof(reg), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nWrite operation in readRegister16 ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterReadBuf(ADXL345_ADDRESS, (uint8 *) readBuffer, sizeof(readBuffer), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nRead operation in readRegister16 ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
    I2C_I2CMasterClearStatus();
    return (int16_t) (readBuffer[0x01] << 0x08 | readBuffer[0x00]);   
}

void writeRegister(uint8_t reg, uint8_t cmd)
{
    uint8 writeBuffer[0x02] = {0};
    writeBuffer[0] = reg;
    writeBuffer[1] = cmd;
    
    uint8 status = I2C_I2CMasterWriteBuf(ADXL345_ADDRESS, (uint8 *) writeBuffer, sizeof(writeBuffer), I2C_I2C_MODE_COMPLETE_XFER);
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nWrite operation ended with error!");
    I2C_I2CMasterClearStatus();
    
}

void showRange()
{
  printf("\r\nADXL Range: ");
 
  switch(getRange())
  {
    case ADXL345_RANGE_16G: printf("+/- 16 g"); break;
    case ADXL345_RANGE_8G:  printf("+/- 8 g");  break;
    case ADXL345_RANGE_4G:  printf("+/- 4 g");  break;
    case ADXL345_RANGE_2G:  printf("+/- 2 g");  break;
    default: printf("Unknown range"); break;
  }
}

void showMeasurementRate(void)
{
  printf("\r\nMeasurement rate: ");
 
  switch(getMeasurementRate())
  {
    case ADXL345_DATARATE_3200HZ: printf("3200 Hz"); break;
    case ADXL345_DATARATE_1600HZ: printf("1600 Hz"); break;
    case ADXL345_DATARATE_800HZ:  printf("800 Hz");  break;
    case ADXL345_DATARATE_400HZ:  printf("400 Hz");  break;
    case ADXL345_DATARATE_200HZ:  printf("200 Hz");  break;
    case ADXL345_DATARATE_100HZ:  printf("100 Hz");  break;
    case ADXL345_DATARATE_50HZ:   printf("50 Hz");   break;
    case ADXL345_DATARATE_25HZ:   printf("25 Hz");   break;
    case ADXL345_DATARATE_12_5HZ: printf("12.5 Hz"); break;
    case ADXL345_DATARATE_6_25HZ: printf("6.25 Hz"); break;
    case ADXL345_DATARATE_3_13HZ: printf("3.13 Hz"); break;
    case ADXL345_DATARATE_1_56HZ: printf("1.56 Hz"); break;
    case ADXL345_DATARATE_0_78HZ: printf("0.78 Hz"); break;
    case ADXL345_DATARATE_0_39HZ: printf("0.39 Hz"); break;
    case ADXL345_DATARATE_0_20HZ: printf("0.20 Hz"); break;
    case ADXL345_DATARATE_0_10HZ: printf("0.10 Hz"); break;
    default: printf("Rate unknown"); break;
  }
}





/* [] END OF FILE */
