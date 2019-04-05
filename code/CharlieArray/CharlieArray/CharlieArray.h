#ifndef CharlieArray_h
#define CharlieArray_h

#include "Arduino.h"
#include <Charlieplex.h>

class CharlieArray{
  public:
    CharlieArray(int arrayLen, charliePin ledPins[])
    void draw();
    void setPixel(int i, brightness);
  private:
    int arrayLen;
    byte brightnesss[100];
    charliePin ledPins[];
    }

#endif
