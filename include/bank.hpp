#pragma once
#include<arduino.h>



class ButtonMgr{ //ボタンマネージャ
    public:

    class Bank{
    int number;
    String bankname;

    class Button{ //ボタンパラメタ
    public:
    int volume;
    int volarc;
    String samplename;

    Button(){volume = 100;}
    };
    };

    ButtonMgr::Bank bank[13];
    

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


