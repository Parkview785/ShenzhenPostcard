#include "Arduino.h"
#include "CharlieArray.h"
#include <Charlieplex.h>

CharlieArray::CharlieArray(int arrayLen, charliePin *ledPins, Charlieplex *charlieplex){
  _arrayLen = arrayLen;
  _ledPins = ledPins;
  _charlieplex = charlieplex;
}
CharlieArray::CharlieArray(){
}

void CharlieArray::setPixel(int pixel, int brightness){
  _brightnesss[pixel] = brightness;
}

void CharlieArray::draw(){
     _charlieplex->charlieWrite(_ledPins[1], HIGH);
     Serial.println(_ledPins[1].vcc);

}

void CharlieArray::clear(){
  for(int pixel = 0; pixel < _arrayLen; pixel++){
       _brightnesss[pixel] = 0;
  }
}

