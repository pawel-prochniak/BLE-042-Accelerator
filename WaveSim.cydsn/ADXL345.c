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

uint16 rawDataX, rawDataY, rawDataZ;

union SomeUnion 
{
    float32 fl;
    char ch[4];
    uint8 u[4];
} someUnion;

void startAccConnection() 
{      
    CyDelay(50); // wait for initialization
    writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    
    printf("\r\n--- Some Union tests ---");
    printf("\r\nRandom float (12.04f): %f", 12.04f);
    someUnion.fl = 12.3f;
    printf("\r\nUnion float value (12.3f): %f", someUnion.fl);
    printf("\r\n--- Tests ended ---\r\n");
    
    printf("\r\nStarted measurement mode\r\n");
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
    /*
    xData.floatVal = 12.9f;
    debug("Fake float: ");
    debugFloat(xData.floatVal);
    */
    
    xData.floatVal = (float) (rawDataX * SCALE_FACTOR);
    yData.floatVal = (float) (rawDataY * SCALE_FACTOR);
    zData.floatVal = (float) (rawDataZ * SCALE_FACTOR);
    
    /*
    debug("Scaled 1st byte: ");
    debugInt(xData.uintVal[0]);
    debug("Scaled float: ");
    debugFloat(xData.floatVal);
    debug("");
    */
    
}

void setMeasurementRate(DataRate_t range) 
{
    writeRegister(ADXL345_REG_BW_RATE, range);
}

DataRate_t getMeasurementRate() 
{
    return (DataRate_t) (readRegister(ADXL345_REG_BW_RATE) & 0xF0);
}

void setRange(Range_t range) 
{
    uint8 value = getRange();
    
  // Update the data rate
  // (&) 0b11110000 (0xF0 - Leave MSB)
  // (|) 0b0000xx?? (range - Set range)
  // (|) 0b00001000 (0x08 - Set Full Res)
    
    value &= 0xF0;
    value |= range;
    value |= 0x08;
    
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

uint8 readRegister(uint8 reg)
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

long readRegister16(uint8 reg) 
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
    return readBuffer[0x00] << 0x08 | readBuffer[0x01];   
}

void writeRegister(uint8 reg, uint8 cmd)
{
    uint8 writeBuffer[0x02] = {0};
    writeBuffer[0] = reg;
    writeBuffer[1] = cmd;
    
    uint8 status = I2C_I2CMasterWriteBuf(ADXL345_ADDRESS, (uint8 *) writeBuffer, sizeof(writeBuffer), I2C_I2C_MODE_COMPLETE_XFER);
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    if (status != I2C_I2C_MSTR_NO_ERROR) printf("\r\nWrite operation ended with error!");
    I2C_I2CMasterClearStatus();
    
}





/* [] END OF FILE */
