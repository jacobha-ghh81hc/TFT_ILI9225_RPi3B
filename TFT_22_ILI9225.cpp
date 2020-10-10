// Include application, user and local libraries
#include "TFT_22_ILI9225.h"
#include "SPI_CONFIG.h"

// Constructor when using hardware SPI.
TFT_22_ILI9225::TFT_22_ILI9225(int8_t RST, int8_t RS, int8_t CS) : SPI_Configuration(RST, RS, CS)
{
    gfxFont = NULL;
}

TFT_22_ILI9225::TFT_22_ILI9225(const SPI_Configuration & spi_cfg) : SPI_Configuration(spi_cfg)
{
    gfxFont = NULL;
}

void TFT_22_ILI9225::begin (void)
{
    // Start Initial Sequence
    // Set SS bit and direction output from S528 to S1
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
    SPI_Configuration::endWrite();
    delay(40);

    // Power-on sequence
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL4, 0x006F); // Set GVDD 007F 0088
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL1, 0x0800); // Set SAP,DSTB,STB
    SPI_Configuration::endWrite();
    delay(10);
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC
    SPI_Configuration::endWrite();
    delay(50);

    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
    SPI_Configuration::_writeRegister(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
    SPI_Configuration::_writeRegister(ILI9225_ENTRY_MODE, 0x1038); // set GRAM write direction and BGR=1.
    SPI_Configuration::_writeRegister(ILI9225_DISP_CTRL1, 0x0000); // Display off
    SPI_Configuration::_writeRegister(ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
    SPI_Configuration::_writeRegister(ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
    SPI_Configuration::_writeRegister(ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
    SPI_Configuration::_writeRegister(ILI9225_OSC_CTRL, 0x0D01); // Set Osc 0e01
    SPI_Configuration::_writeRegister(ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
    SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
    SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address

    // Set GRAM area
    SPI_Configuration::_writeRegister(ILI9225_GATE_SCAN_CTRL, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB); 
    SPI_Configuration::_writeRegister(ILI9225_PARTIAL_DRIVING_POS2, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 

    // Set GAMMA curve
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL1, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL2, 0x0808); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL3, 0x080A); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL4, 0x000A); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL5, 0x0A08); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL6, 0x0808); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL7, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL8, 0x0A00); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL9, 0x0710); 
    SPI_Configuration::_writeRegister(ILI9225_GAMMA_CTRL10, 0x0710); 

    SPI_Configuration::_writeRegister(ILI9225_DISP_CTRL1, 0x0012); 
    SPI_Configuration::endWrite();
    delay(50); 
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_DISP_CTRL1, 0x1017);
    SPI_Configuration::endWrite();

    // Configure the orientation
    // Init these are uint16_t _maxX, _maxY, _bgColor; uint8_t _orientation;
    setOrientation(0);
    setBackgroundColor(COLOR_BLACK);
    clear();
}

void TFT_22_ILI9225::_orientCoordinates(uint16_t &x1, uint16_t &y1) {
    switch (_orientation) {
        case 0:  // ok
            break;
        case 1: // ok
            y1 = _maxY - y1 - 1;
            _swap(x1, y1);
            break;
        case 2: // ok
            x1 = _maxX - x1 - 1;
            y1 = _maxY - y1 - 1;
            break;
        case 3: // ok
            x1 = _maxX - x1 - 1;
            _swap(x1, y1);
            break;
    }
}

void TFT_22_ILI9225::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    _setWindow( x0, y0, x1, y1, TopDown_L2R ); // default for drawing characters
}


void TFT_22_ILI9225::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, autoIncMode_t mode) {
    DB_PRINT( "setWindows 1st: x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );
    
    // clip to TFT-Dimensions
    x0 = min( x0, (uint16_t) (_maxX-1) );
    x1 = min( x1, (uint16_t) (_maxX-1) );
    y0 = min( y0, (uint16_t) (_maxY-1) );
    y1 = min( y1, (uint16_t) (_maxY-1) );
    _orientCoordinates(x0, y0);
    _orientCoordinates(x1, y1);

    if (x1<x0) _swap(x0, x1);
    if (y1<y0) _swap(y0, y1);
    
    SPI_Configuration::startWrite();
    // autoincrement mode
    if ( _orientation > 0 ) mode = modeTab[_orientation-1][mode];
    SPI_Configuration::_writeRegister(ILI9225_ENTRY_MODE, 0x1000 | ( mode<<3) );
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1,x1);
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2,x0);

    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1,y1);
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2,y0);
    DB_PRINT( "setWindows 2nd: x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );
    // starting position within window and increment/decrement direction
    switch ( mode>>1 ) {
        case 0:
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 1:
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 2:
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
        case 3:
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
    }
    SPI_Configuration::_writeCommand16( ILI9225_GRAM_DATA_REG );

    //SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x0);
    //SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y0);

    //SPI_Configuration::_writeCommand(0x00, 0x22);

    SPI_Configuration::endWrite();
}

void TFT_22_ILI9225::_resetWindow() {
    SPI_Configuration::startWrite(); 
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    SPI_Configuration::_writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    SPI_Configuration::_writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 
    SPI_Configuration::endWrite(); 
}

void TFT_22_ILI9225::clear() {
    uint8_t old = _orientation;
    setOrientation(0);
    fillRectangle(0, 0, _maxX - 1, _maxY - 1, COLOR_BLACK);
    setOrientation(old);
    delay(10);
}

void TFT_22_ILI9225::invert(bool flag) {
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeCommand16(flag ? ILI9225C_INVON : ILI9225C_INVOFF);
    //SPI_Configuration::_writeCommand(0x00, flag ? ILI9225C_INVON : ILI9225C_INVOFF);
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::setDisplay(bool flag) {
    if (flag) {
        SPI_Configuration::startWrite();
        SPI_Configuration::_writeRegister(0x00ff, 0x0000);
        SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL1, 0x0000);
        SPI_Configuration::endWrite();
        delay(50);
        SPI_Configuration::startWrite();
        SPI_Configuration::_writeRegister(ILI9225_DISP_CTRL1, 0x1017);
        SPI_Configuration::endWrite();
        delay(200);
    } else {
        SPI_Configuration::startWrite();
        SPI_Configuration::_writeRegister(0x00ff, 0x0000);
        SPI_Configuration::_writeRegister(ILI9225_DISP_CTRL1, 0x0000);
        SPI_Configuration::endWrite();
        delay(50);
        SPI_Configuration::startWrite();
        SPI_Configuration::_writeRegister(ILI9225_POWER_CTRL1, 0x0003);
        SPI_Configuration::endWrite();
        delay(200);
    }
}

void TFT_22_ILI9225::setOrientation(uint8_t orientation) {

    _orientation = orientation % 4;

    switch (_orientation) {
    case 0:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 1:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    case 2:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 3:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    }
}

uint8_t TFT_22_ILI9225::getOrientation() {
    return _orientation;
}

void TFT_22_ILI9225::drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    SPI_Configuration::startWrite();
    drawLine(x1, y1, x1, y2, color);
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x2, y1, x2, y2, color);
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {

    _setWindow(x1, y1, x2, y2);

    SPI_Configuration::startWrite();
    for (uint16_t t=(y2 - y1 + 1) * (x2 - x1 + 1); t > 0; t--)
        SPI_Configuration::_writeData16(color);
    SPI_Configuration::endWrite();
    _resetWindow();
}


void TFT_22_ILI9225::drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    SPI_Configuration::startWrite();

    drawPixel(x0, y0 + r, color);
    drawPixel(x0, y0-  r, color);
    drawPixel(x0 + r, y0, color);
    drawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 - y, y0 - x, color);
    }
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::fillCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color) {

    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x = 0;
    int16_t y = radius;

    SPI_Configuration::startWrite();
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        drawLine(x0 + x, y0 + y, x0 - x, y0 + y, color); // bottom
        drawLine(x0 + x, y0 - y, x0 - x, y0 - y, color); // top
        drawLine(x0 + y, y0 - x, x0 + y, y0 + x, color); // right
        drawLine(x0 - y, y0 - x, x0 - y, y0 + x, color); // left
    }
    SPI_Configuration::endWrite();
    fillRectangle(x0-x, y0-y, x0+x, y0+y, color);
}


void TFT_22_ILI9225::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {

    // Classic Bresenham algorithm
    int16_t steep = abs((int16_t)(y2 - y1)) > abs((int16_t)(x2 - x1));

    int16_t dx, dy;

    if (steep) {
        _swap(x1, y1);
        _swap(x2, y2);
    }

    if (x1 > x2) {
        _swap(x1, x2);
        _swap(y1, y2);
    }

    dx = x2 - x1;
    dy = abs((int16_t)(y2 - y1));

    int16_t err = dx / 2;
    int16_t ystep;

    if (y1 < y2) ystep = 1;
    else ystep = -1;

    SPI_Configuration::startWrite();
    for (; x1<=x2; x1++) {
        if (steep) drawPixel(y1, x1, color);
        else       drawPixel(x1, y1, color);

        err -= dy;
        if (err < 0) {
            y1 += ystep;
            err += dx;
        }
    }
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::drawPixel(uint16_t x1, uint16_t y1, uint16_t color) {

    if((x1 >= _maxX) || (y1 >= _maxY)) return;

    // _setWindow(x1, y1, x1+1, y1+1);
    // _orientCoordinates(x1, y1);
    // SPI_Configuration::startWrite();
    // //SPI_Configuration::_writeData(color >> 8, color);
    // SPI_Configuration::_writeData16(color);
    // SPI_Configuration::endWrite();

    _orientCoordinates(x1, y1);
    SPI_Configuration::startWrite();
    SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET1,x1);
    SPI_Configuration::_writeRegister(ILI9225_RAM_ADDR_SET2,y1);
    SPI_Configuration::_writeRegister(ILI9225_GRAM_DATA_REG,color);
    SPI_Configuration::endWrite();
}


uint16_t TFT_22_ILI9225::maxX() {
    return _maxX;
}


uint16_t TFT_22_ILI9225::maxY() {
    return _maxY;
}


uint16_t TFT_22_ILI9225::setColor(uint8_t red8, uint8_t green8, uint8_t blue8) {
    // rgb16 = red5 green6 blue5
    return (red8 >> 3) << 11 | (green8 >> 2) << 5 | (blue8 >> 3);
}


void TFT_22_ILI9225::splitColor(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue) {
    // rgb16 = red5 green6 blue5
    red   = (rgb & 0b1111100000000000) >> 11 << 3;
    green = (rgb & 0b0000011111100000) >>  5 << 2;
    blue  = (rgb & 0b0000000000011111)       << 3;
}


void TFT_22_ILI9225::_swap(uint16_t &a, uint16_t &b) {
    uint16_t w = a;
    a = b;
    b = w;
}


void TFT_22_ILI9225::drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) {
    SPI_Configuration::startWrite();
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::fillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) {

    uint16_t a, b, y, last;

    // Sort coordinates by Y order (y3 >= y2 >= y1)
    if (y1 > y2) {
        _swap(y1, y2); _swap(x1, x2);
    }
    if (y2 > y3) {
        _swap(y3, y2); _swap(x3, x2);
    }
    if (y1 > y2) {
        _swap(y1, y2); _swap(x1, x2);
    }

    SPI_Configuration::startWrite();
    if (y1 == y3) { // Handle awkward all-on-same-line case as its own thing
        a = b = x1;
        if (x2 < a)      a = x2;
        else if (x2 > b) b = x2;
        if (x3 < a)      a = x3;
        else if (x3 > b) b = x3;
            drawLine(a, y1, b, y1, color);
        return;
    }

    int16_t dx11 = x2 - x1,
            dy11 = y2 - y1,
            dx12 = x3 - x1,
            dy12 = y3 - y1,
            dx22 = x3 - x2,
            dy22 = y3 - y2;
    int32_t sa   = 0,
            sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y2=y3 (flat-bottomed triangle), the scanline y2
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y2 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y1=y2
    // (flat-topped triangle).
    if (y2 == y3) last = y2;   // Include y2 scanline
    else          last = y2 - 1; // Skip it

    for (y = y1; y <= last; y++) {
        a   = x1 + sa / dy11;
        b   = x1 + sb / dy12;
        sa += dx11;
        sb += dx12;
        // longhand:
        // a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        // b = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
        if (a > b) _swap(a,b);
        drawLine(a, y, b, y, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y2=y3.
    sa = dx22 * (y - y2);
    sb = dx12 * (y - y1);
    for (; y<=y3; y++) {
        a   = x2 + sa / dy22;
        b   = x1 + sb / dy12;
        sa += dx22;
        sb += dx12;
        // longhand:
        // a = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
        // b = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
        if (a > b) _swap(a,b);
            drawLine(a, y, b, y, color);
    }
    SPI_Configuration::endWrite();
}


void TFT_22_ILI9225::setBackgroundColor(uint16_t color) {
    _bgColor = color;
}


void TFT_22_ILI9225::setFont(uint8_t* font, bool monoSp) {

    cfont.font     = font;
    cfont.width    = readFontByte(0);
    cfont.height   = readFontByte(1);
    cfont.offset   = readFontByte(2);
    cfont.numchars = readFontByte(3);
    cfont.nbrows   = cfont.height / 8;
    cfont.monoSp   = monoSp;

    if (cfont.height % 8) cfont.nbrows++;  // Set number of bytes used by height of font in multiples of 8
}


_currentFont TFT_22_ILI9225::getFont() {
    return cfont;
}


uint16_t TFT_22_ILI9225::drawText(uint16_t x, uint16_t y, STRING s, uint16_t color) {

    uint16_t currx = x;

    // Print every character in string
#ifdef USE_STRING_CLASS
    for (uint8_t k = 0; k < s.length(); k++) {
        currx += drawChar(currx, y, s.at(k), color) + 1;
    }
#else
    for (uint8_t k = 0; k < strlen(s); k++) {
        currx += drawChar(currx, y, s[k], color) + 1;
    }
#endif
    return currx;
}


uint16_t TFT_22_ILI9225::getTextWidth( STRING s ) {

    uint16_t width = 0;
    // Count every character in string ( +1 for spacing )
#ifdef USE_STRING_CLASS
    for (uint8_t k = 0; k < s.length(); k++) {
        width += getCharWidth(s.at(k) ) + 1;
    }
#else
    for (uint8_t k = 0; k < strlen(s); k++) {
        width += getCharWidth(s[k]) + 1;
    }
#endif
    return width;
}


uint16_t TFT_22_ILI9225::drawChar(uint16_t x, uint16_t y, uint16_t ch, uint16_t color) {

    uint8_t charData, charWidth;
    uint8_t h, i, j;
    uint16_t charOffset;
    bool fastMode;

    charOffset = (cfont.width * cfont.nbrows) + 1;  // bytes used by each character
    charOffset = (charOffset * (ch - cfont.offset)) + FONT_HEADER_SIZE;  // char offset (add 4 for font header)
    if ( cfont.monoSp ) charWidth = cfont.width;      // monospaced: get char width from font
    else                charWidth  = readFontByte(charOffset);  // get chracter width from 1st byte
    charOffset++;  // increment pointer to first character data byte

    SPI_Configuration::startWrite();
    
    // use autoincrement/decrement feature, if character fits completely on screen
    fastMode = ( (x+charWidth+1) < _maxX && (y+cfont.height-1) < _maxY );
    
    if (fastMode) _setWindow( x,y,x+charWidth+1, y+cfont.height-1 );  // set character Window

    for (i = 0; i <= charWidth; i++) {  // each font "column" (+1 blank column for spacing)
        h = 0;  // keep track of char height
        for (j = 0; j < cfont.nbrows; j++)     {  // each column byte
            if (i == charWidth) charData = (uint8_t)0x0; // Insert blank column
            else                charData = readFontByte(charOffset);
            charOffset++;
            
            // Process every row in font character
            for (uint8_t k = 0; k < 8; k++) {
                if (h >= cfont.height ) break;  // No need to process excess bits
                if (fastMode) SPI_Configuration::_writeData16( bitRead(charData, k)?color:_bgColor );
                else drawPixel( x + i, y + (j * 8) + k, bitRead(charData, k)?color:_bgColor );
                h++;
            }
        }
    }
    SPI_Configuration::endWrite();
    _resetWindow();
    return charWidth;
}


uint16_t TFT_22_ILI9225::getCharWidth(uint16_t ch) {
    uint16_t charOffset;
    charOffset = (cfont.width * cfont.nbrows) + 1;  // bytes used by each character
    charOffset = (charOffset * (ch - cfont.offset)) + FONT_HEADER_SIZE;  // char offset (add 4 for font header)

    return readFontByte(charOffset);  // get font width from 1st byte
}


// Draw a 1-bit image (bitmap) at the specified (x,y) position from the
// provided bitmap buffer (must be PROGMEM memory) using the specified
// foreground color (unset bits are transparent).
void TFT_22_ILI9225::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  0, true, true, false );
}

// Draw a 1-bit image (bitmap) at the specified (x,y) position from the
// provided bitmap buffer (must be PROGMEM memory) using the specified
// foreground (for set bits) and background (for clear bits) colors.
void TFT_22_ILI9225::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  bg, false, true, false );
}


// drawBitmap() variant for RAM-resident (not PROGMEM) bitmaps.
void TFT_22_ILI9225::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  0, true, false, false );
}


// drawBitmap() variant w/background for RAM-resident (not PROGMEM) bitmaps.
void TFT_22_ILI9225::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  bg, false, false, false );
}


//Draw XBitMap Files (*.xbm), exported from GIMP,
//Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
//C Array can be directly used with this function
void TFT_22_ILI9225::drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  0, true, true, true );
}


void TFT_22_ILI9225::drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    _drawBitmap( x,  y, bitmap,  w,  h, color,  bg, false, true, true );
}


// internal function for drawing bitmaps with/without transparent bg, or from ram or progmem
void TFT_22_ILI9225::_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg, bool transparent, bool progmem,bool Xbit) {
    bool noAutoInc = false;     // Flag set when transparent pixel was 'written'
    int16_t i, j, byteWidth = (w + 7) / 8;
    int16_t wx0, wy0, wx1, wy1, wh;  // Window-position and size
	// int16_t ww;
    uint8_t byte, maskBit;
	byte = 0;
    maskBit = Xbit? 0x01:0x80;
    // adjust window hight/width to displaydimensions
    DB_PRINT( "DrawBitmap.. maxX=%d, maxY=%d", _maxX,_maxY );
    wx0 = x < 0 ? 0 : x;
    wy0 = y < 0 ? 0 : y;
    wx1 = (x + w > _maxX ?_maxX : x + w ) - 1;
    wy1 = (y + h > _maxY ?_maxY : y + h ) - 1;
    wh  = wy1 - wy0 + 1;
    // ww  = wx1 - wx0 + 1;
    _setWindow(wx0, wy0, wx1, wy1, L2R_TopDown);
    SPI_Configuration::startWrite();
    for (j = y>=0?0:-y; j < (y>=0?0:-y)+wh; j++) {
        for (i = 0; i < w; i++ ) {
            if (i & 7) { 
                if ( Xbit ) byte >>=1; else byte <<= 1; 
            }
            else {
                if ( progmem ) byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
                else           byte   = bitmap[j * byteWidth + i / 8];
            }
            if ( x+i >= wx0 && x+i <= wx1 ) {
                // write only if pixel is within window
                if (byte & maskBit) {
                    if (noAutoInc) {
                        //there was a transparent area, set pixelkoordinates again
                        drawPixel(x + i, y + j, color);
                        noAutoInc = false;
                    }
                    else  { 
                        SPI_Configuration::_writeData16(color);
                    }
                }
                else  {
                    if (transparent) noAutoInc = true; // no autoincrement in transparent area!
                    else SPI_Configuration::_writeData16( bg);
                }
            }
        }
    }
    SPI_Configuration::endWrite();
}


//Draw XBitMap Files (*.xbm), exported from GIMP,
//Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
//C Array can be directly used with this function
/*
void TFT_22_ILI9225::drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte;

    SPI_Configuration::startWrite();
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++ ) {
            if (i & 7) byte >>= 1;
            else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            if (byte & 0x01) drawPixel(x + i, y + j, color);
        }
    }
    SPI_Configuration::endWrite();
}
*/


//High speed color bitmap
void TFT_22_ILI9225::drawBitmap(uint16_t x1, uint16_t y1, const uint16_t** bitmap, int16_t w, int16_t h) {
    _setWindow(x1, y1, x1+w-1, y1+h-1, L2R_TopDown);
    SPI_Configuration::startWrite();
    SPI_Configuration::_spiDCHigh();
    SPI_Configuration::_spiCSLow();
    for (uint16_t y = 0; y < h; y++) {
#ifdef HSPI_WRITE_PIXELS
        HSPI_WRITE_PIXELS(bitmap[y], w * sizeof(uint16_t));
        continue;
#endif
        for (uint16_t x = 0; x < w; x++) {
            SPI_Configuration::_spiWrite16(bitmap[y][x]);
        }
    }
    SPI_Configuration::_spiCSHigh();
    SPI_Configuration::endWrite();
}


//High speed color bitmap
void TFT_22_ILI9225::drawBitmap(uint16_t x1, uint16_t y1, uint16_t** bitmap, int16_t w, int16_t h) {
    _setWindow(x1, y1, x1+w-1, y1+h-1, L2R_TopDown);
    SPI_Configuration::startWrite();
    SPI_Configuration::_spiDCHigh();
    SPI_Configuration::_spiCSLow();
    for (uint16_t y = 0; y < h; y++) {
#ifdef HSPI_WRITE_PIXELS
        HSPI_WRITE_PIXELS(bitmap[y], w * sizeof(uint16_t));
        continue;
#endif
        for (uint16_t x = 0; x < w; x++) {
            SPI_Configuration::_spiWrite16(bitmap[y][x]);
        }
    }
    SPI_Configuration::_spiCSHigh();
    SPI_Configuration::endWrite();
}


//1-D array High speed color bitmap
void TFT_22_ILI9225::drawBitmap(uint16_t x1, uint16_t y1, const uint16_t* bitmap, int16_t w, int16_t h) {
    _setWindow(x1, y1, x1+w-1, y1+h-1, L2R_TopDown);
    SPI_Configuration::startWrite();
    SPI_Configuration::_spiDCHigh();
    SPI_Configuration::_spiCSLow();
#ifdef HSPI_WRITE_PIXELS
    HSPI_WRITE_PIXELS(bitmap, w * h * sizeof(uint16_t));
#else    
    for (uint16_t i = 0; i < h * w; ++i) {
        SPI_Configuration::_spiWrite16(bitmap[i]);
    }
#endif    
    SPI_Configuration::_spiCSHigh();
    SPI_Configuration::endWrite();
}


//1-D array High speed color bitmap
void TFT_22_ILI9225::drawBitmap(uint16_t x1, uint16_t y1, uint16_t* bitmap, int16_t w, int16_t h) {
    _setWindow(x1, y1, x1+w-1, y1+h-1, L2R_TopDown);
    SPI_Configuration::startWrite();
    SPI_Configuration::_spiDCHigh();
    SPI_Configuration::_spiCSLow();
#ifdef HSPI_WRITE_PIXELS
    HSPI_WRITE_PIXELS(bitmap, w * h * sizeof(uint16_t));
#else    
    for (uint16_t i = 0; i < h * w; ++i) {
        SPI_Configuration::_spiWrite16(bitmap[i]);
    }
#endif    
    SPI_Configuration::_spiCSHigh();
    SPI_Configuration::endWrite();
}


// TEXT- AND CHARACTER-HANDLING FUNCTIONS ----------------------------------

void TFT_22_ILI9225::setGFXFont(const GFXfont *f) {
    gfxFont = (GFXfont *)f;
}


// Draw a string
void TFT_22_ILI9225::drawGFXText(int16_t x, int16_t y, STRING s, uint16_t color) {

    int16_t currx = x;

    if(gfxFont) {
        // Print every character in string
#ifdef USE_STRING_CLASS
        for (uint8_t k = 0; k < s.length(); k++) {
            currx += drawGFXChar(currx, y, s.at(k), color) + 1;
        }
#else
        for (uint8_t k = 0; k < strlen(s); k++) {
            currx += drawGFXChar(currx, y, s[k], color) + 1;
        }
#endif
    }
}


// Draw a character
uint16_t TFT_22_ILI9225::drawGFXChar(int16_t x, int16_t y, unsigned char c, uint16_t color) {

    c -= (uint8_t)pgm_read_byte(&gfxFont->first);
    GFXglyph *glyph  = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
    uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&gfxFont->bitmap);

    uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
    uint8_t  w  = pgm_read_byte(&glyph->width),
             h  = pgm_read_byte(&glyph->height),
             xa = pgm_read_byte(&glyph->xAdvance);
    int8_t   xo = pgm_read_byte(&glyph->xOffset),
             yo = pgm_read_byte(&glyph->yOffset);
    uint8_t  xx, yy, bits = 0, bit = 0;

    // Add character clipping here one day

    SPI_Configuration::startWrite();
    for(yy=0; yy<h; yy++) {
        for(xx=0; xx<w; xx++) {
            if(!(bit++ & 7)) {
                bits = pgm_read_byte(&bitmap[bo++]);
            }
            if(bits & 0x80) {
                drawPixel(x+xo+xx, y+yo+yy, color);
            }
            bits <<= 1;
        }
    }
    SPI_Configuration::endWrite();

    return (uint16_t)xa;
}


void TFT_22_ILI9225::getGFXCharExtent(uint8_t c, int16_t *gw, int16_t *gh, int16_t *xa) {
    uint8_t first = pgm_read_byte(&gfxFont->first),
            last  = pgm_read_byte(&gfxFont->last);
    // Char present in this font?
    if((c >= first) && (c <= last)) {
        GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c - first]);
        *gw = pgm_read_byte(&glyph->width);
        *gh = pgm_read_byte(&glyph->height);
        *xa = pgm_read_byte(&glyph->xAdvance);
        // int8_t  xo = pgm_read_byte(&glyph->xOffset),
        //         yo = pgm_read_byte(&glyph->yOffset);
    }
}

void TFT_22_ILI9225::getGFXTextExtent(STRING str, int16_t x, int16_t y, int16_t *w, int16_t *h) {
    *w  = *h = 0;
#ifdef USE_STRING_CLASS
    for (uint8_t k = 0; k < str.length(); k++) {
        uint8_t c = str.at(k);
#else
    for (uint8_t k = 0; k < strlen(str); k++) {
        uint8_t c = str[k];
#endif
        int16_t gw, gh, xa;
        getGFXCharExtent(c, &gw, &gh, &xa);
        if(gh > *h) {
            *h = gh;
        }
        *w += xa;
    }
}
