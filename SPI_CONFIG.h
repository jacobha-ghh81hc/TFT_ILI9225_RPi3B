#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

#define DEBUG
#ifdef DEBUG
    #define DB_PRINT( ... ) { char dbgbuf[60]; sprintf( dbgbuf, __VA_ARGS__ ); std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << dbgbuf << std::endl; }
#else
    #define DB_PRINT( ... )
#endif

#define McCauley
#ifdef McCauley
    #include <bcm2835.h>
#else
    #include <sys/ioctl.h>
    #include <linux/spi/spidev.h>
#endif

// Hardware SPI Macros 
#define SPI_BEGIN_TRANSACTION()    bcm2835_spi_begin()
#define SPI_END_TRANSACTION()      bcm2835_spi_end()

#define HSPI_WRITE(b)               bcm2835_spi_transfer(b)
#define HSPI_WRITE16(s)             bcm2835_spi_write(s)
#define HSPI_WRITE_PIXELS(c,l)      for (uint32_t i=0; i<(l); i+=2) { HSPI_WRITE(((uint8_t*)(c))[i+1]); HSPI_WRITE(((uint8_t*)(c))[i]); }

class SPI_Configuration
{
private:
	uint32_t writeFunctionLevel;
	int8_t  _rst, _rs, _cs;

public:
	SPI_Configuration(int8_t RST, int8_t RS, int8_t CS);
	void _spiBegin(void);
	void _spiWrite(uint8_t b);
    void _spiWrite16(uint16_t s);
    void _spiWriteCommand(uint8_t c);
    void _spiWriteData(uint8_t d);

    void _spiDCHigh(void);
    void _spiDCLow(void);
    void _spiCSHigh(void);
    void _spiCSLow(void);

    void _writeRegister(uint16_t reg, uint16_t data);
    void _writeData(uint8_t HI, uint8_t LO);
    void _writeData16(uint16_t HILO);
    void _writeCommand(uint8_t HI, uint8_t LO);
    void _writeCommand16(uint16_t HILO);
	void startWrite(void);
    void endWrite(void);
};


#endif