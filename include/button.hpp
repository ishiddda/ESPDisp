#pragma once
#include<arduino.h>

class Button{ //ボタンパラメタ
  public:
  int volume;
  int volarc;
  String samplename;

  Button(){volume = 100;}
};

class ButtonMgr{ //ボタンマネージャ
    public:
    Button button[13]; // ボタン実体

    int RetVol(int number){
      return button[number].volume;
    };

    int CalcArc(int number){
      return button[number].volarc = button[number].volume * 3.6;
    };

    int RetArc(int number){
      return button[number].volarc;
    };

    void SetVol(int number, int newvalue){
      button[number].volume = newvalue;
    };
};

int retvol(int n);
int retarc(int n);
void setvol(int n, int newvalue);
