// Include application, user and local libraries
#include "TFT_22_ILI9225.h"

// [Pin connection]
// ILI9225-SPI-------------------------------------RPi(Pin#)
// CS---------TFT_CS------GPIO8 Chip select--------RPI_V2_GPIO_P1_24--Pin#24
// RST--------TFT_RST-----GPIO3 Reset--------------RPI_V2_GPIO_P1_05--Pin#5
// RS(DC)-----TFT_RS------GPIO2 0=COMMAND/1=DATA---RPI_V2_GPIO_P1_03--Pin#3
// SDA--------TFT_SDI-----GPIO10 SPI0_MOSI---------Pin#19
// CLK--------TFT_CLK-----GPIO11 SPI0_CLK----------Pin#23
// GND--------0V----------GND----------------------Pin#6
// VCC--------3.3V--------VCC----------------------Pin#1

#define TFT_RST RPI_BPLUS_GPIO_J8_05
#define TFT_RS RPI_BPLUS_GPIO_J8_03
#define TFT_CS RPI_BPLUS_GPIO_J8_24

// Use hardware SPI
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS);

/*
 * Tux black/white image in 180x220 converted using Ardafruit bitmap converter
 * https://github.com/ehubin/Adafruit-GFX-Library/tree/master/Img2Code
 */
static const uint8_t tux[] = 
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x1,0xfc,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x7,0xfe,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1,0xf8,0x0,0xf,0xff,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3,0xfc,0x0,0x1f,0xff,0x80,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7,0xfe,0x0,0x1f,0xff,0xc0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7,0xfe,0x0,0x3f,0xff,0xc0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf,0xff,0x0,0x3f,0xff,0xe0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf,0xff,0x0,0x7f,0xf,0xe0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf,0xbf,0x80,0x7e,0x7,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf,0xf,0x80,0x7c,0x7,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x7,0x80,0x78,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x7,0x80,0x78,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x7,0x80,0x78,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x3,0x80,0x78,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x3,0x0,0x38,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x0,0x0,0x0,0x3,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x0,0xff,0xc0,0x3,0xe0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x6,0x1,0xff,0xf8,0x3,0xe0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7,0x7,0xff,0xfc,0x7,0xe0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0x8f,0xff,0xff,0x7,0xc0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0x1f,0xff,0xff,0xc0,0x80,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x3f,0xff,0xff,0xf8,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1,0xff,0xff,0xff,0xff,0xc0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf,0xff,0xff,0xff,0xff,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf,0xff,0xff,0xff,0xfe,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x19,0xff,0xff,0xff,0xf8,0x70,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x18,0xff,0xff,0xff,0xe0,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1c,0x7f,0xff,0xff,0x87,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xe,0x3f,0xff,0xff,0xf,0xe0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7,0x1f,0xff,0xfc,0x3f,0xc0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7,0x87,0xff,0xf0,0xff,0x80,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3,0xe1,0xff,0xc3,0xff,0x10,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0xf0,0x38,0xf,0xfe,0x38,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x7e,0x0,0x3f,0xf8,0x78,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x2,0x1f,0xe7,0xff,0xc1,0xf8,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x3,0x8f,0xff,0xff,0x7,0xfc,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x3,0xc7,0xff,0xfe,0x3f,0xfc,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3,0xe3,0xff,0xf8,0x7f,0xfc,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7,0xf0,0xff,0xe1,0xff,0xfe,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7,0xfc,0x3f,0x7,0xff,0xfe,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x7,0xfe,0x0,0x1f,0xff,0xfe,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x7,0xff,0xc0,0xff,0xff,0xff,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x7,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0xf,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0xf,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x2,0x0,0x0,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1,0x0,0x0,0x7f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x80,0x0,0x3f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x40,0x0,0x3f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x20,0x0,0x1f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0xf,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x10,0x0,0xf,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xc0,0x10,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x8,0x0,0x7,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0x80,0x20,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x7,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0x0,0x20,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x4,0x0,0x3,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0x0,0x40,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x2,0x0,0x1,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfe,0x0,0x40,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x2,0x0,0x1,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfe,0x0,0x80,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x1,0x0,0x0,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfc,0x0,0x80,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x1,0x0,0x0,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfc,0x1,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x1,0x80,0x0,0x7f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf8,0x1,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x80,0x0,0x7f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf8,0x2,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0xc0,0x0,0x7f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf0,0x2,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0xc0,0x0,0x3f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf0,0x6,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x40,0x0,0x3f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xe0,0x4,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x60,0x0,0x1f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xe0,0x4,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x60,0x0,0x1f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xc0,0xc,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x60,0x0,0x1f,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xc0,0xc,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x60,0x0,0xf,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xc0,0x8,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x30,0x0,0xf,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x80,0x8,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x30,0x0,0xf,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x80,0x18,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x30,0x0,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x80,0x18,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x30,0x0,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x0,0x18,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x30,0x0,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x0,0x18,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x30,0x0,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x0,0x18,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x70,0x0,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfe,0x0,0x18,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x70,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfe,0x0,0x18,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x70,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfe,0x0,0x18,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x70,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfe,0x0,0x18,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xf0,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x18,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x1c,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x1c,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x1c,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x3e,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x1e,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x7,0x80,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0xe,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1e,0x1,0xe0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0xf,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3f,0xc0,0x70,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x7,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7f,0xf0,0x38,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0xf8,0xc,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xff,0xfe,0x6,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0x2,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0x3,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x7f,0xff,0x3,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xfc,0x1e,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x84,0x7f,0xff,0x3,0x7,0xff,0xff,0xf0,
0xff,0xff,0xff,0xf8,0x7f,0x80,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc,0x7f,0xfe,0x2,0xf,0xff,0xff,0xf0,
0xff,0xff,0xff,0xf0,0xff,0xe0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1e,0x7f,0xfe,0x0,0xf,0xff,0xff,0xf0,
0xff,0xff,0xff,0xe1,0xff,0xf0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1e,0x3f,0xfc,0x0,0x3,0xff,0xff,0xf0,
0xff,0xff,0xff,0xc3,0xff,0xf8,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3e,0x1f,0xf0,0x0,0x1,0xff,0xff,0xf0,
0xff,0xff,0xff,0xc7,0xff,0xfc,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3e,0xf,0xe0,0xf,0xe0,0xff,0xff,0xf0,
0xff,0xff,0xff,0x87,0xff,0xfe,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0x2,0x0,0x1f,0xf8,0x7f,0xff,0xf0,
0xff,0xff,0xff,0xf,0xff,0xfe,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0x80,0x0,0x3f,0xfc,0x7f,0xff,0xf0,
0xff,0xff,0xfe,0x1f,0xff,0xff,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0x80,0x0,0xff,0xfc,0x3f,0xff,0xf0,
0xff,0xff,0xf8,0x3f,0xff,0xff,0x80,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x7f,0xc0,0x3,0xff,0xfe,0x3f,0xff,0xf0,
0xff,0xff,0xc0,0x7f,0xff,0xff,0x80,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xf0,0xf,0xff,0xfe,0x3f,0xff,0xf0,
0xff,0xff,0x0,0xff,0xff,0xff,0xc0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0x1f,0xff,0xf0,
0xff,0xfc,0x3,0xff,0xff,0xff,0xc0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0x1f,0xff,0xf0,
0xff,0xf0,0x1f,0xff,0xff,0xff,0xe0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0x1f,0xff,0xf0,
0xff,0xe0,0xff,0xff,0xff,0xff,0xe0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0xf,0xff,0xf0,
0xff,0xe1,0xff,0xff,0xff,0xff,0xf0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xf0,
0xff,0xc3,0xff,0xff,0xff,0xff,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xf8,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xf0,
0xff,0x87,0xff,0xff,0xff,0xff,0xf8,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0x87,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xfc,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xfc,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xfe,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xfe,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0x80,0x1,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xf8,0x7f,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xc0,0x1,0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xf0,
0xff,0x87,0xff,0xff,0xff,0xff,0xff,0xc0,0x3,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xfe,0x3f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xe0,0x7,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xfe,0x1f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xf0,0xf,0xff,0xff,0xff,0xff,0xff,0xe3,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xf8,0x7f,0xff,0xff,0xff,0xff,0xff,0xe3,0xff,0xff,0xff,0xff,0xff,0xff,0xf,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xf8,0x7f,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xfe,0x1f,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xf,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xf,0xf0,
0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0x87,0xff,0xff,0xff,0xff,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xfe,0x1f,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xf8,0xf,0xff,0xff,0xff,0xff,0xff,0xf8,0x3f,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xff,0xff,0xff,0xe0,0xf,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xf0,
0xff,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x7f,0xff,0xff,0xff,0x80,0x1f,0xff,0xff,0xff,0xff,0xff,0xc0,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xfe,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0x3,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3,0xff,0xff,0xf0,0x0,0x1f,0xff,0xff,0xff,0xff,0xfc,0x7,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x3f,0xfe,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xc0,0x7f,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0x1,0xff,0xff,0xf0,
0xff,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xfc,0x7,0xff,0xff,0xf0,
0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xf8,0x1f,0xff,0xff,0xf0,
0xff,0x87,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,0xf0,
0xff,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,0xf0,
0xff,0xe0,0xf,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xf0,
0xff,0xf0,0x0,0xf,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0x87,0xff,0xff,0xff,0xf0,
0xff,0xfc,0x0,0x0,0x7f,0xff,0xff,0xff,0xf8,0x0,0x1f,0xff,0xf0,0x0,0x3f,0xff,0xff,0xff,0xf,0xff,0xff,0xff,0xf0,
0xff,0xff,0xe0,0x0,0x7,0xff,0xff,0xff,0xf8,0x7,0xff,0xff,0xff,0xfe,0x1f,0xff,0xff,0xfe,0x1f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xc0,0x0,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0x1f,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x0,0x3f,0xff,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xf,0xff,0xff,0xf8,0x7f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf0,0xf,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfe,0x3,0xff,0xff,0x87,0xff,0xff,0xff,0xff,0xff,0x87,0xff,0xff,0xc1,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0x80,0x3f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xf8,0x1f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xf,0x80,0x3f,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0
};


int main (void)
{
	tft.begin();

	RUNNING:
	tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
	tft.setFont(Terminal12x16);
	tft.drawText(10, 10, "hello!");
	delay(1000);
  
	tft.clear();
	tft.drawText(10, 20, "clear");
	delay(1000);

	tft.drawText(10, 30, "text small");
	tft.setBackgroundColor(COLOR_YELLOW);
	tft.setFont(Terminal6x8);
	tft.drawText(90, 30, "BIG", COLOR_RED);
	tft.setBackgroundColor(COLOR_RED);
	tft.setFont(Terminal12x16);
	delay(1000);

	tft.drawRectangle(10, 10, 110, 110, COLOR_BLUE);
	tft.drawText(10, 60, "rectangle");
	delay(1000);

	tft.fillRectangle(20, 20, 120, 120, COLOR_RED);
	tft.drawText(10, 70, "solidRectangle");
	delay(1000);

	tft.drawCircle(80, 80, 50, COLOR_YELLOW);
	tft.drawText(10, 80, "circle");
	delay(1000);

	tft.fillCircle(90, 90, 30, COLOR_GREEN);
	tft.drawText(10, 90, "solidCircle");
	delay(1000);

	tft.drawLine(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_CYAN);
	tft.drawText(10, 100, "line");
	delay(1000);
	
	for (uint8_t i = 0; i < 4; i++) {
		tft.clear();
		tft.setOrientation(i);
		tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
		tft.drawText(10, 10, "setOrientation (" + std::string("0123").substr(i, i + 1) + ")", COLOR_YELLOWGREEN);
		tft.drawRectangle(10, 20, 50, 60, COLOR_GREEN);
		tft.drawCircle(70, 80, 10, COLOR_BLUE);
		tft.drawLine(30, 40, 70, 80, COLOR_YELLOW);
		delay(1000);
	}

	tft.setOrientation(0);
	tft.clear();
	tft.drawText(10, 100, "drawing bitmap");
	delay(1000);
	tft.clear();
	tft.setBackgroundColor(COLOR_RED);
	tft.drawBitmap(0, 0, tux, 180, 220, COLOR_WHITE);
	delay(5000);

	tft.clear();
	tft.drawPixel(10, 20, COLOR_RED);
	delay(3000);
	tft.drawText(10, 110, "point");
	delay(1000);

	tft.setOrientation(0);
	tft.clear();
	tft.setFont(Terminal12x16);
	tft.setBackgroundColor(COLOR_YELLOW);
	tft.drawText(10, 40, "bye!", COLOR_RED);
	tft.setBackgroundColor(COLOR_GREEN);
	tft.setFont(Terminal6x8);
	delay(1000);
  
	tft.drawText(10, 60, "off");
	delay(1000);
	goto RUNNING;

	tft.setDisplay(false);

	return 0;
}
