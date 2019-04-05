#include "Arduino.h"
#include "CharlieArray.h"
#include <Charlieplex>

CharlieArray::CharlieArray(int arrayLen, charliePin ledPins){
  arrayLen = arrayLen
  brightnesss = [0]*100;
  ledPins = ledPins;
}

void CharlieArray::setPixel(int pixel, byte brightness){
  brightnesss[pixel] = brightness;
}

void CharlieArray::draw(){
  //do nothing;
}
