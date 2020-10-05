# TFT_ILI9225_RPi3B

How to compile the sample program
- Install the bcm2835 library as prerequite condition
- Run this command:
arm-linux-gnueabihf-g++ -o Basic_Demo.out Basic_Demo.cpp TFT_22_ILI9225.h TFT_22_ILI9225.cpp gfxfont.h DefaultFonts.c -I/usr/local/include -L/usr/local/lib -lbcm2835 -lm -lpthread -DSPI -DBCM
