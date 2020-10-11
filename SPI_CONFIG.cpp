#include "SPI_CONFIG.h"

// Constructor when using hardware SPI.
SPI_Configuration::SPI_Configuration(int8_t rst, int8_t rs, int8_t cs) {
    _rst  = rst;
    _rs   = rs;
    _cs   = cs;
    writeFunctionLevel = 0;
}

void SPI_Configuration::_spiDCHigh(void) { bcm2835_gpio_write(_rs, HIGH); }
void SPI_Configuration::_spiDCLow(void) { bcm2835_gpio_write(_rs, LOW); }
void SPI_Configuration::_spiCSHigh(void) { bcm2835_gpio_write(_cs, HIGH); }
void SPI_Configuration::_spiCSLow(void) { bcm2835_gpio_write(_cs, LOW); }
void SPI_Configuration::_spiResetTFT(void)
{
    bcm2835_gpio_fsel(_rst, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(_rst, LOW); // Pull the reset pin low to reset ILI9225
    bcm2835_delay(100);
    bcm2835_gpio_write(_rst, HIGH); // Pull the reset pin high to release the ILI9225C from the reset status
    bcm2835_delay(100);
}

void SPI_Configuration::_spiBegin (void)
{
	if (!bcm2835_init()) { DB_PRINT("Function bcm2835_init is error\n"); return; }

    // Set up reset pin
    bcm2835_gpio_fsel(_rst, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(_rst, LOW);

    // Control pins
    bcm2835_gpio_fsel(_rs, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(_rs, LOW);
    bcm2835_gpio_fsel(_cs, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(_cs, HIGH);

    // Hardware SPI
    if (!bcm2835_spi_begin()) { DB_PRINT("Function bcm2835_spi_begin is error\n"); return; }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);

    // Initialization Code
    bcm2835_gpio_write(_rst, HIGH); // Pull the reset pin high to release the ILI9225C from the reset status
    delay(1); 
    bcm2835_gpio_write(_rst, LOW); // Pull the reset pin low to reset ILI9225
    delay(10);
    bcm2835_gpio_write(_rst, HIGH); // Pull the reset pin high to release the ILI9225C from the reset status
    delay(50);
}

void SPI_Configuration::_spiWrite(uint8_t b) {
    HSPI_WRITE(b);
}

void SPI_Configuration::_spiWrite16(uint16_t s) {
    HSPI_WRITE16(s);
}

void SPI_Configuration::_spiWriteCommand(uint8_t c) {
    _spiDCLow();
    _spiCSLow();
    _spiWrite(c);
    _spiCSHigh();
}

void SPI_Configuration::_spiWriteData(uint8_t d) {
    _spiDCHigh();
    _spiCSLow();
    _spiWrite(d);
    _spiCSHigh();
}

void SPI_Configuration::_writeRegister(uint16_t reg, uint16_t data) {
    _writeCommand16(reg);
    _writeData16(data);
}

void SPI_Configuration::_writeData(uint8_t HI, uint8_t LO) {
    _spiWriteData(HI);
    _spiWriteData(LO);
}

void SPI_Configuration::_writeData16(uint16_t data) {
    _spiDCHigh();
    _spiCSLow();
#ifdef HSPI_WRITE16
    HSPI_WRITE16(data);
#else 
    HSPI_WRITE(data >> 8);
    HSPI_WRITE(0x00ff & data);
#endif
    _spiCSHigh();
}

void SPI_Configuration::_writeCommand(uint8_t HI, uint8_t LO) {
    _spiWriteCommand(HI);
    _spiWriteCommand(LO);
}

void SPI_Configuration::_writeCommand16(uint16_t command) {
    _spiDCLow();
    _spiCSLow();
#ifdef HSPI_WRITE16
    HSPI_WRITE16(command);
#else
    HSPI_WRITE(command >> 8);
    HSPI_WRITE(0x00ff & command);
#endif
    _spiCSHigh();
}

void SPI_Configuration::startWrite(void) {
    if (writeFunctionLevel++ == 0) {
        SPI_BEGIN_TRANSACTION();
        _spiCSLow();
    }
}

void SPI_Configuration::endWrite(void) {
    if (--writeFunctionLevel == 0) {
        _spiCSHigh();
        SPI_END_TRANSACTION();
    }
}