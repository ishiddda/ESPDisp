#pragma once
#include<arduino.h>

#include<rotary.h>
#include<GFX.h>
#include<button.hpp>

//エンコーダ実体
AiEsp32RotaryEncoder *rotaryEncoder = new AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);
AiEsp32RotaryEncoderNumberSelector numberSelector = AiEsp32RotaryEncoderNumberSelector();

void IRAM_ATTR readEncoderISR(){
  rotaryEncoder->readEncoder_ISR();
}

//エンコーダー値を読み込む関数
int ValueLoad(int ValueMin, int ValueMax){
int Value = (int)numberSelector.getValue();
if(Value > ValueMax){numberSelector.setValue(ValueMin); Value = (int)numberSelector.getValue();}
if(Value < ValueMin){numberSelector.setValue(ValueMax); Value = (int)numberSelector.getValue();}
return Value;
};


//シーン管理
class Scene{
public:
enum State {
   State_PLAY,
   State_BANK,
   State_SAMPLE,
   State_VOLUME
};

public:
int CurrentBank = 1;
int CurrentSample = 1;

public:
Scene():state_(State_SAMPLE){}

int play(){
  if (rotaryEncoder->isEncoderButtonClicked()){
    Serial.print(CurrentSample);
    return 0;
  }else{
  bankdraw(CurrentBank);
  sampledraw(0);
  buttondraw(0);
  volumedraw(0);
  return 1;
  }
};

int bank(){
  numberSelector.setRange(1.0, 5.0, 1, false, 0);
  int value = numberSelector.getValue();
  if (rotaryEncoder->isEncoderButtonClicked()){
    CurrentBank = ValueLoad(1,5);
    Serial.print(CurrentSample);
    return 0;
  }else{
  bankdraw(value);
  sampledraw(0);
  buttondraw(0);
  volumedraw(0);
  drawpointer(1);
  return 1;
  }
};

int sample(){
  numberSelector.setRange(1.0, 9.0, 1, false, 0);
  //numberSelector.setValue(1.0);
  int value = numberSelector.getValue();
  value = ValueLoad(1,9);
  if (rotaryEncoder->isEncoderButtonClicked()){
  CurrentSample = value;
  Serial.print(CurrentSample);
  return 0;
  }else{
  bankdraw(CurrentBank);
  sampledraw(value);
  buttondraw(value);
  volumedraw(0);
  drawpointer(10);
  return 1;
  }
};  

int volume(){
  numberSelector.setRange(-retvol(CurrentSample), 100-retvol(CurrentSample), 1, false, 0);
  int value = retvol(CurrentSample) + ValueLoad(-retvol(CurrentSample)-1, 100-retvol(CurrentSample)+1);
  if (rotaryEncoder->isEncoderButtonClicked()){
  setvol(CurrentSample, value);
  Serial.print(CurrentSample);
  CurrentSample = 1;
  return 0;
  }else{

  bankdraw(CurrentBank);
  sampledraw(CurrentSample);
  drawbuttonvol(CurrentSample, value * 3.6);
  volumedraw(value);    
  drawpointer(21);
  return 1;
  }
}

bool update() {
   bool isEnd = false;
      switch( state_ ) {
      case State_PLAY:
         if ( play() == 0 )
            state_ = State_BANK;    // バンクへ
         break;
      case State_BANK:     
        if ( bank() == 0 )
            state_ = State_SAMPLE;    // バンクへ
         break;
      case State_SAMPLE:
         if ( sample() == 0 )
            state_ = State_VOLUME;    // タイトルへ
         break;
      case State_VOLUME:
      if( volume() ==0)
      state_ = State_PLAY;
      }
   return isEnd;
}

private:
State state_;
};
