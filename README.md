# presepe-1.0
sketch to conrol a strip of WS2812B with Ardino UNO, Nano or Digispark

Requires: FastLED 3.1.0 library

Arduino circuit is really simple.
Connect the strip of WS2812B to 5V, GND and D3 pin.

The sketch implements these effects:
fire: to simulate the effect of a camfire
sunrise/sunset: to simulate the rising and settin Sun. At low brightness the light is yellowish/orangeish.
on/off: the classic on and off effect
4 color changes

Change the effect duration modifying the const variables:

pi_intervalA  (on/off)
pi_intervalB  (4 colors)
pi_intervalGN (sunrise/sunset)
 
Change colors and effects A and B modifying these arrays: 
int lampeggia_colori_A[2][3]={
  {32,255,100},
  {32,255,0}
  };

int lampeggia_colori_B[4][3]={
  {60,255,100},
  {96,255,100},
  {128,255,100},
  {128,0,100}
  };
