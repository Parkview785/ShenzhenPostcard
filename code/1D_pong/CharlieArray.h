/*Things to fix:
 * frame rate
 * 
 */

#ifndef CharlieArray_h
#define CharlieArray_h

#include "Arduino.h"
#include <Charlieplex.h>

class CharlieArray{
  public:
    CharlieArray(int arrayLen, charliePin ledPins[], Charlieplex *charlieplex);
    CharlieArray();
    void draw();
    void setPixel(int i, int brightness);
    void clear();
  private:
    int _arrayLen;
    int *_brightnesss;
    charliePin *_ledPins;
    Charlieplex *_charlieplex;
    
    };

#endif
