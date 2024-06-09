#include<Arduino.h>
#include <GFX.h>
#include <rotary.h>
#include <scene.hpp>
#include <button.hpp>
#include<settings.hpp>

//インスタンス生成
Scene scene; 

void setup(void){
    Serial.begin(9600);

    //Rotary
    rotaryEncoder->begin();
    rotaryEncoder->setup(readEncoderISR);
    numberSelector.attachEncoder(rotaryEncoder);
    numberSelector.setRange(0.0, 10.0, 1, false, 0);
    numberSelector.setValue(1.0);

    //LCD
    lcdinit();
    lcdcreate();

    



    delay(500);
}

void loop(void){

  ReadIniFile();
   
  //scene.update();
  //lcdpush();     

  delay(1000);
}


