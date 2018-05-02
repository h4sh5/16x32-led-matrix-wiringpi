# 16x32-led-matrix-wiringpi
Library based on wiringpi to display things on an ultrathin 16x32 led matrix board using the raspberry pi.

Check the script comment for wiring up the display. The wiring is using a Raspberry Pi 3, but remapping is easy.

The LED board is available at:
https://tronixlabs.com.au/display/led/matrix/ultrathin-16x32-red-led-matrix-panel-australia/
https://www.littlebirdelectronics.com.au/ultrathin-16x32-red-led-matrix-panel
https://www.ebay.com/sch/i.html?_nkw=16x32+led
etc.

Running the welcome.c example:
```
# apt install wiringpi
# gcc -o welcome -l wiringPi welcome.c 
# ./welcome
```
