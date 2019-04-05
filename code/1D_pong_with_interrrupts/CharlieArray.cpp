#include "Arduino.h"
#include "CharlieArray.h"
#include <Charlieplex.h>

CharlieArray::CharlieArray(int arrayLen, charliePin ledPins[], Charlieplex *charlieplex){
  _arrayLen = arrayLen;
  _brightnesss =  new int [arrayLen];
  _ledPins = ledPins;
  _charlieplex = charlieplex;
}
CharlieArray::CharlieArray(){
}

void CharlieArray::setPixel(int pixel, int brightness){
  _brightnesss[pixel] = brightness;
}

void CharlieArray::draw(){
  for(int pixel = 0; pixel < _arrayLen; pixel++){
    if(_brightnesss[pixel] != 0){
     _charlieplex->charlieWrite(_ledPins[pixel], HIGH);
     delay(0.1);
     _charlieplex->clear();
    }
  }
}

void CharlieArray::clear(){
  for(int pixel = 0; pixel < _arrayLen; pixel++){
       _brightnesss[pixel] = 0;
  }
}

