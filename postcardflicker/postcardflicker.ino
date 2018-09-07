//Unfinished led patterns for postcard. Used to make pretty patterns on charlie plexed LEDs.
//Problems with charlieplexing and pwm together. Clock speed of attiny just not fast enough


#include <Charlieplex.h>


// button stuff
const int button = 0;
int buttonState = 0;
int lastButtonState = 0;
int state = 0;
int states = 5;

#define NUMBER_OF_PINS 4
byte pins[] = {1,2,3,4};
Charlieplex charlieplex = Charlieplex(pins,NUMBER_OF_PINS);

charliePin leds[] = {{0,3},{3,0},{0,1},{1,0},{3,1},{1,3},{2,1},{1,2},{2,3},{3,2},{2,0},{0,2}};

class LedStrip{
  int len;
  charliePin *pins;
  byte brightnesss[100];
  charliePin pin1;
  int randLed = 0;
  int randTime = 0;
  unsigned long previousMillis;
  unsigned long previousMillis2;
  bool areAllOn = false;
  int updateTime = 10;
  signed int currentLed = len;
  bool movingUp =true;
  
public:
  LedStrip(int stripLen, charliePin ledPins[]){
    len = stripLen;
    pins = ledPins;
  }
  
  void allOn(byte brightness){
     for(int i = 0; i < len; i++){
        setLed(i, brightness);
     }
  }
    void discoFlash(){
      if((millis()-previousMillis) >randTime){
        previousMillis = millis();
        randLed = random(len);
        randTime = random(20);
        setLed(randLed, 255*random(2));
      }
    }

    void setLed(int led, byte brightness){
      if((led <len) && (led>=0)){
        brightnesss[led] = brightness;
      }
    }
    void dimLed(int led, int amount){
      if(brightnesss[led] >0){
        brightnesss[led]-=amount;
      }
    }

    void draw(){
      for(int i = 0; i < len; i++){
        if (brightnesss[i] != 0){
         charlieplex.charlieWrite(leds[i],HIGH);
         delay(brightnesss[i]/1000);
         charlieplex.clear();
        }
      }
    }

    void flashFade(int period){
      if((millis()-previousMillis) > period){
        previousMillis = millis();
        randLed = random(len);
        setLed(randLed, 255);
      }
      if((millis()-previousMillis2) > 10){
        previousMillis2 = millis();
        for(int i = 0; i < len; i++){
          dimLed(i, 10);
          }
      }
    }

    void flash(int period){
      if((millis()-previousMillis) > period){
         previousMillis = millis();
         if(areAllOn == true){
          allOn(0);
          areAllOn = false;
         }
         else{
          allOn(255);
          areAllOn = true;
         }
      }
    }

    void nAtATime(int period,int n){
      if((millis()-previousMillis) > period){
         previousMillis = millis();
         setLed(currentLed, 0);
         currentLed = (currentLed+1)%len;
         for(int i = 0; i < n; i++){
          setLed((currentLed+i)%len, 255);
         }
         
      }
    }

    void nightRider(int period, int n){
      if((millis()-previousMillis) > period){
         previousMillis = millis();
         if(movingUp){
          setLed(currentLed, 0);
          currentLed = (currentLed+1);
          for(int i = 0; i < n; i++){
              setLed((currentLed+i), 255);
           }
           if(currentLed == (len-1)){
           currentLed = len+(n-2);//leave last on led on
           movingUp = false;
           }
         }
          else{
            setLed(currentLed, 0);
            currentLed = (currentLed-1);
            for(int i = 0; i < n; i++){
              setLed((currentLed-i), 255);
           }
           if(currentLed == 0){
           currentLed = (-n+1);//leave on led on
           movingUp = true;
           }
          }
          
         }
    }
};


 
LedStrip ledStrip = LedStrip(12, leds);

void setup(){ 
  randomSeed(analogRead(0));
  pinMode(button, INPUT);
 }
 
void loop(){
  lastButtonState = buttonState;
  buttonState = digitalRead(button);
  if((lastButtonState != buttonState) && (buttonState == 1)){
    state = (state+1)%states;
    ledStrip.allOn(0);
  }
  
  switch(state){
    case(0):
      ledStrip.nightRider(10,4);
      break;
    case(1):
      ledStrip.allOn(255);
      break;
    case(2):
      ledStrip.discoFlash();
      break;
    case(3):
      ledStrip.flash(50);
      break;
    case(4):
      ledStrip.nAtATime(10,4);
  }
  ledStrip.draw();
  
}


