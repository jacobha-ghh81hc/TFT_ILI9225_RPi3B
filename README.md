# TFT_ILI9225_RPi3B

How to compile the sample program
- Install the WiringPi and bcm2835 library as prerequite condition
- Run this command:
arm-linux-gnueabihf-g++ -o basicDemo Basic_Demo.cpp TFT_22_ILI9225.h TFT_22_ILI9225.cpp gfxfont.h DefaultFonts.c -lwiringPi -lbcm2835 -lm -lpthread -DWPI