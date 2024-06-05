#pragma once
#include<arduino.h>

class Button{ //ボタンパラメタ
  public:
  int bankn;
  int volume;
  int volarc;
  String samplename;

  Button(){volume = 100; bankn =1;}
};

class ButtonMgr{ //ボタンマネージャ
    public:
    Button button[13][13]; // ボタン実体

    int RetVol(int banknum, int samplenum){
      return button[banknum][samplenum].volume;
    };

    int CalcArc(int banknum, int samplenum){
      return button[banknum][samplenum].volarc = button[banknum][samplenum].volume * 3.6;
    };

    int RetArc(int banknum, int samplenum){
      return button[banknum][samplenum].volarc;
    };

    void SetVol(int banknum, int samplenum, int newvalue){
      button[banknum][samplenum].volume = newvalue;
    };
};

int retvol(int b, int s);
int retarc(int b, int s);
void setvol(int b, int s, int newvalue);
