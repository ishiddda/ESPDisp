#include<button.hpp>

ButtonMgr btnmgr;

int retvol(int b, int s){
  return btnmgr.RetVol(b, s);
}

int retarc(int b, int s){
    return btnmgr.CalcArc(b, s);
}

void setvol(int b, int s, int value){
    btnmgr.SetVol(b, s, value);
}