#include <Charlieplex.h>
#include "CharlieArray.h"

#define START_SPEED 1
#define LEDS 12

// Define button pin on PCB
const int button = 0;

// Create Charlieplex
byte pins[] = {1,2,3,4};
Charlieplex charlieplex = Charlieplex(pins,4);
charliePin leds[] = {{0,3},{3,0},{0,1},{1,0},{3,1},{1,3},{2,1},{1,2},{2,3},{3,2},{2,0},{0,2}};

// Create CharlieArray
CharlieArray ledStrip = CharlieArray(LEDS, leds, &charlieplex);

void setup(){ 
  pinMode(button, INPUT);
  Serial.begin(9600);
}



void loop(){
    ledStrip.draw();
}

 
 
