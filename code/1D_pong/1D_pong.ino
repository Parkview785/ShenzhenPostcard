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
}

class pongGame{
  public:
    pongGame(){
      _gameOver = 0;
      _speed = START_SPEED;
      _previousMillis = 0;
      _currentLed = 0;
      _direction = 1;
    }
    
    void start(){
      _gameOver = false;
      while(!_gameOver){
        updateLeds();
        checkButton();
        ledStrip.draw();
      }
    }
    
  private:
    bool _gameOver;
    int _speed;
    bool _direction;
    int _currentLed;
    unsigned long _previousMillis;
    int _lastButtonState;

    
    void updateLeds(){
      int currentMillis = millis();
      if((currentMillis - _previousMillis) > (1000/_speed)){ // update LEDs according to speed
        _previousMillis = currentMillis;
        if(((_currentLed == 0) && (_direction == 0)) || 
            ((_currentLed == LEDS - 1) && (_direction == 1))){ // Player misses the ball
          gameOver();
        }
        else{ 
          _currentLed = _currentLed + (_direction * 1) - (!_direction * 1); //move one along
        }
        ledStrip.clear();
        ledStrip.setPixel(_currentLed, 255);
      }
    }

    void checkButton(){
      int buttonState = digitalRead(button);
      if (buttonState != _lastButtonState){
        _lastButtonState = buttonState;
        if(buttonState){
          if(((_currentLed == 0) && (_direction == 0)) || 
            ((_currentLed == LEDS - 1) && (_direction == 1))){
              _speed += 1;
              _direction = !_direction;
            }
          else{
            gameOver();
          }
        }
      }
    }

    void gameOver(){
      _speed = START_SPEED;
      _direction = 1;
      _currentLed = 0;
      _gameOver == true;
      flash();
    }

    void flash(){
      for(int i = 0; i < 3; i++){
        for(int pixel = 0; pixel < LEDS; pixel++){
          ledStrip.setPixel(pixel, 255);
        }
        _previousMillis = millis();
        while((millis()-_previousMillis)<500){
        ledStrip.draw();
        }
        ledStrip.clear();
        _previousMillis = millis();
        while((millis()-_previousMillis)<500){
        ledStrip.draw();
        }
      }
    }

    
};




pongGame game = pongGame();

void loop(){
  game.start();
}

 
 
