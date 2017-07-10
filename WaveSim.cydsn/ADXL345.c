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

bool startAccConnection() 
{      
    CyDelay(50); // wait for initialization
    writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    debug("Started measurement mode");
    
    return true;
}

uint8 getDeviceId() 
{    
    return readRegister(ADXL345_REG_DEVID);
}

void getRawDataX() 
{
    rawDataX = readRegister16(ADXL345_REG_DATAX0);
    debug("Raw X: ");
    debugInt(rawDataX);
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
    xData.floatVal = rawDataX * SCALE_FACTOR;
    yData.floatVal = rawDataY * SCALE_FACTOR;
    zData.floatVal = rawDataZ * SCALE_FACTOR;
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
    if (status != I2C_I2C_MSTR_NO_ERROR) debug("Write operation in readRegister ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterReadBuf(ADXL345_ADDRESS, (uint8 *) readBuffer, sizeof(readBuffer), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) debug("Read operation in readRegister ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT));
    I2C_I2CMasterClearStatus();
    return readBuffer[0x00];
}

long readRegister16(uint8 reg) 
{
    static uint8 readBuffer[0x02];
    uint8 status = I2C_I2CMasterWriteBuf(ADXL345_ADDRESS, &reg, sizeof(reg), I2C_I2C_MODE_COMPLETE_XFER);
    if (status != I2C_I2C_MSTR_NO_ERROR) debug("Write operation in readRegister16 ended with error!");
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT));
    I2C_I2CMasterClearStatus();
    status = I2C_I2CMasterReadBuf(ADXL345_ADDRESS, (uint8 *) readBuffer, sizeof(readBuffer), I2C_I2C_MODE_COMPLETE_XFER);
        if (status != I2C_I2C_MSTR_NO_ERROR) debug("Read operation in readRegister16 ended with error!");
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
    if (status != I2C_I2C_MSTR_NO_ERROR) debug("Write operation ended with error!");
    I2C_I2CMasterClearStatus();
    
}





/* [] END OF FILE */
