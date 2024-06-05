#include<Arduino.h>
#include<GFX.h>
#include<rotary.h>
#include<button.hpp>

using namespace std;

#define BG TFT_LIGHTGRAY
#define C1 TFT_WHITE
#define C2 TFT_SILVER
#define C3 TFT_ORANGE

LGFX_7735 lcd;

void titledraw(){
    lcd.setTextColor(TFT_WHITE);
    lcd.print("       __    ____  ______\n");
    lcd.print("      / /   / __ \\/ ____/\n");
    lcd.print("     / /   / /_/ / /     \n");
    lcd.print("    / /___/ ____/ /___   \n");
    lcd.print("   /_____/_/    \\____/   \n");
    delay(500);

    lcd.print(" \n");

    lcd.print(" Setup");
    lcd.print("."); delay(500);
    lcd.print("."); delay(500);
    lcd.print("."); delay(500);
    lcd.print(" Ready.\n"); delay(500);
    lcd.print(" LPC Sampler version 1.0\n"); delay(300);
    lcd.print(" processor:  Teensy41\n"); delay(300);
    lcd.print(" SD Loading...\n"); delay(300);
    lcd.print(" SD card is connected.\n"); delay(300);
    lcd.print(" SD library is able to \n"); delay(300);
    lcd.print(" access the filesystem\n"); delay(300);
}

void lcdinit(){
    lcd.init();
    lcd.setRotation(3);
    lcd.setBrightness(128);
    lcd.setColorDepth(24);
    lcd.setBaseColor(BG);
    lcd.fillScreen(BG);

    titledraw();   

    lcd.clear();

}


static LGFX_Sprite sprite1(&lcd);     //lcd all
static LGFX_Sprite sprite2(&sprite1); //bank
static LGFX_Sprite sprite3(&sprite1); //sample
static LGFX_Sprite sprite4(&sprite1); //1
static LGFX_Sprite sprite5(&sprite1); //2
static LGFX_Sprite sprite6(&sprite1); //3
static LGFX_Sprite sprite7(&sprite1); //4 fx1
static LGFX_Sprite sprite8(&sprite1); //5
static LGFX_Sprite sprite9(&sprite1); //6
static LGFX_Sprite sprite10(&sprite1); //7
static LGFX_Sprite sprite11(&sprite1); //8 fx2
static LGFX_Sprite sprite12(&sprite1); //9
static LGFX_Sprite sprite13(&sprite1); //10
static LGFX_Sprite sprite14(&sprite1); //11
static LGFX_Sprite sprite15(&sprite1); //12 fx3
static LGFX_Sprite sprite16(&sprite1); //pointer
static LGFX_Sprite sprite17(&sprite1); //



void drawbutton1(int bank, int sample, int vol){
sprite4.createSprite(27,27);
  sprite4.fillScreen(BG);
  sprite4.fillCircle(13,13,8,C1);
  if(sample == 1){ //該当時
    sprite4.fillArc(13,13,10,13,0, vol, C2);
    sprite4.fillCircle(13,13,8,C2);
  }else if(sample == 0){ //無選択時 
    sprite4.fillCircle(13,13,8,C1);
    sprite4.fillArc(13,13,10,13,0, retarc(bank,1), C1);
  }else{     
    sprite4.fillArc(13,13,10,13,0, retarc(bank,1), C1); 
  }  
  sprite4.pushSprite(6,37);
}

void drawbutton2(int bank, int sample, int vol){
  sprite5.createSprite(27,27);
  sprite5.fillScreen(BG);
  sprite5.fillCircle(13,13,8,C1);
  if(sample == 2){
  sprite5.fillArc(13,13,10,13,0,vol,C2);
  sprite5.fillCircle(13,13,8,C2);
  }else{
    sprite5.fillArc(13,13,10,13,0,retarc(bank,2),C1);
  }
  sprite5.pushSprite(35,37);
}

void drawbutton3(int bank, int sample, int vol){
  sprite6.createSprite(27,27);
  sprite6.fillScreen(BG);
  sprite6.fillCircle(13,13,8,C1);
  if(sample == 3){
    sprite6.fillArc(13,13,10,13,0,vol,C2);
    sprite6.fillCircle(13,13,8,C2);
  }else{
  sprite6.fillArc(13,13,10,13,0,retarc(bank,3),C1);
  }
  sprite6.pushSprite(64,37);
}

void drawbutton4(int bank, int sample, int volume){
  sprite8.createSprite(27,27);
  sprite8.fillScreen(BG);
  sprite8.fillCircle(13,13,8,C1);
  if(sample == 4){
    sprite8.fillArc(13,13,10,13,0,volume,C2);
    sprite8.fillCircle(13,13,8,C2);
  }else{
  sprite8.fillArc(13,13,10,13,0, retarc(bank,4),C1);
  }
  sprite8.pushSprite(6,66);
}

void drawbutton5(int bank, int sample, int volume){
  sprite9.createSprite(27,27);
  sprite9.fillScreen(BG);
  sprite9.fillCircle(13,13,8,C1);
  if(sample == 5){
    sprite9.fillArc(13,13,10,13,0,volume,C2);
    sprite9.fillCircle(13,13,8,C2);
  }else{
    sprite9.fillArc(13,13,10,13,0,retarc(bank,5),C1);
  }
  sprite9.pushSprite(35,66);
}

void drawbutton6(int bank, int sample, int volume){
  sprite10.createSprite(27,27);
  sprite10.fillScreen(BG);
  sprite10.fillCircle(13,13,8,C1);
  if(sample == 6){
  sprite10.fillArc(13,13,10,13,0,volume,C2);
  sprite10.fillCircle(13,13,8,C2);
  }else{
    sprite10.fillArc(13,13,10,13,0,retarc(bank,6),C1);
  }
  sprite10.pushSprite(64,66);
}

void drawbutton7(int bank, int sample, int volume){
  sprite12.createSprite(27,27);
  sprite12.fillScreen(BG);
  sprite12.fillCircle(13,13,8,C1);
  if(sample == 7){
    sprite12.fillArc(13,13,10,13,0,volume,C2);
    sprite12.fillCircle(13,13,8,C2);
  }else{
  sprite12.fillArc(13,13,10,13,0,retarc(bank,7),C1);
  }
  sprite12.pushSprite(6,95);
}

void drawbutton8(int bank, int sample, int volume){
 sprite13.createSprite(27,27);
  sprite13.fillScreen(BG);
  sprite13.fillCircle(13,13,8,C1);
  if(sample == 8){
    sprite13.fillArc(13,13,10,13,0,volume,C2);
    sprite13.fillCircle(13,13,8,C2);
  }else{
  sprite13.fillArc(13,13,10,13,0,retarc(bank,8),C1);
  }  
  sprite13.pushSprite(35,95);
}

void drawbutton9(int bank, int sample, int volume){
  sprite14.createSprite(27,27);
  sprite14.fillScreen(BG);
  sprite14.fillCircle(13,13,8,C1);
  if(sample == 9){
    sprite14.fillArc(13,13,10,13,0,volume,C2);
    sprite14.fillCircle(13,13,8,C2);
  }else{
  sprite14.fillArc(13,13,10,13,0,retarc(bank,9),C1);
  }  
  sprite14.pushSprite(64,95);

}

void drawbutton10(){
  sprite7.createSprite(27,27);
  sprite7.fillScreen(BG);
  sprite7.fillCircle(13,13,8,C1);
  sprite7.fillArc(13,13,10,13,0,360,C1);
  sprite7.pushSprite(93,37);
}

void drawbutton11(){
  sprite11.createSprite(27,27);
  sprite11.fillScreen(BG);
  sprite11.fillCircle(13,13,8,C1);
  sprite11.fillArc(13,13,10,13,0,360,C1);
  sprite11.pushSprite(93,66);
}

void drawbutton12(){
  sprite15.createSprite(27,27);
  sprite15.fillScreen(BG);
  sprite15.fillCircle(13,13,8,C1);
  sprite15.fillArc(13,13,10,13,0,360,C1);
  sprite15.pushSprite(93,95);
}

void buttondraw(int bank, int value){
  drawbutton1(bank, value, retarc(bank,1));
  drawbutton2(bank, value, retarc(bank,2));
  drawbutton3(bank, value, retarc(bank,3));
  drawbutton4(bank, value, retarc(bank,4));
  drawbutton5(bank, value, retarc(bank,5));
  drawbutton6(bank, value, retarc(bank,6));
  drawbutton7(bank, value, retarc(bank,7));
  drawbutton8(bank, value, retarc(bank,8));
  drawbutton9(bank, value, retarc(bank,9));
  drawbutton10();
  drawbutton11();
  drawbutton12();
  
}

void drawbuttonvol(int bank, int value, int vol){
  drawbutton1(bank, value, vol);
  drawbutton2(bank, value, vol);
  drawbutton3(bank, value, vol);
  drawbutton4(bank, value, vol);
  drawbutton5(bank, value, vol);
  drawbutton6(bank, value, vol);
  drawbutton7(bank, value, vol);
  drawbutton8(bank, value, vol);
  drawbutton9(bank, value, vol);
  drawbutton10();
  drawbutton11();
  drawbutton12();
}

String songname[6] = {"", "three out", "Catchball Rules", "makiba","NOP","9ine Thirty"};
String samplename[13] = {"", "da", "sa", "synth1", "synth2", "synth3","synth4","synth","synth","synth","synth","synth","synth"};

void lcdcreate(){
    sprite1.createSprite(160,128);
  sprite1.fillScreen(BG);
}

void lcdpush(){
    sprite1.pushSprite(0,0);
}

void bankdraw(int Sample){
  sprite2.createSprite(160,10);
  sprite2.fillRect(0,0,160,10,BG);
  sprite2.setCursor(13,2);
  sprite2.setFont(&fonts::Font0);
  sprite2.setTextColor(TFT_DARKGRAY);
  sprite2.printf("BANK%2d  :",Sample);
  sprite2.print(songname[Sample]);
  sprite2.pushSprite(0,0); 
}

void sampledraw(int Sample){
  sprite3.createSprite(160,10);
  sprite3.fillRect(0,0,160,10,BG);
  sprite3.setCursor(13,2);
  sprite3.setFont(&fonts::Font0);
  sprite3.setTextColor(TFT_DARKGRAY);
  
  sprite3.printf("SAMPLE  :");
  sprite3.print(samplename[Sample]);
  sprite3.pushSprite(0,10);
}

void volumedraw(int Sample){
sprite3.createSprite(160,10);
  sprite3.fillRect(0,0,160,10,BG);
  sprite3.setCursor(13,2);
  sprite3.setFont(&fonts::Font0);
  sprite3.setTextColor(TFT_DARKGRAY);
  sprite3.printf("VOLUME  :");
  if(Sample == 0){
    sprite3.print("");
  }else{
  sprite3.print(Sample);
  }
  sprite3.pushSprite(0,20);
}

void drawpointer(int hight){
  sprite16.createSprite(10,10);
  sprite16.fillScreen(BG);
  sprite16.fillTriangle(4,0,8,4,4,8,TFT_DARKGRAY);
  sprite16.pushSprite(0,hight); 
}