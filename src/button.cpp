#include<button.hpp>

ButtonMgr btnmgr;

int retvol(int n){
  return btnmgr.RetVol(n);
}

int retarc(int n){
    return btnmgr.CalcArc(n);
}

void setvol(int n, int value){
    btnmgr.SetVol(n, value);
}