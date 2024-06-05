#include<Arduino.h>
#include<GFX.h>
#include<rotary.h>
#include<button.hpp>

using namespace std;

#define BG TFT_LIGHTGRAY
#define C1 TFT_WHITE
#define C2 TFT_SILVER
#define C3 TFT_ORANGE

#define xst 6  //ButtonStart x
#define yst 37 //ButtonStart y
#define spc 29 //ButtonSpace

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
    //titledraw();   
    lcd.clear();
}


static LGFX_Sprite sprite1(&lcd);     //lcd all
static LGFX_Sprite sprite2(&sprite1); //bank
static LGFX_Sprite sprite3(&sprite1); //sample

static LGFX_Sprite sprite4(&sprite1); //1
static LGFX_Sprite sprite5(&sprite1); //2
static LGFX_Sprite sprite6(&sprite1); //3
//static LGFX_Sprite sprite[10](&sprite1); //4 fx1
static LGFX_Sprite sprite8(&sprite1); //5
static LGFX_Sprite sprite9(&sprite1); //6
static LGFX_Sprite sprite10(&sprite1); //7
//static LGFX_Sprite sprite[11](&sprite1); //8 fx2
static LGFX_Sprite sprite12(&sprite1); //9
static LGFX_Sprite sprite13(&sprite1); //10
static LGFX_Sprite sprite14(&sprite1); //11
//static LGFX_Sprite sprite[12](&sprite1); //12 fx3

static LGFX_Sprite sprite16(&sprite1); //pointer
static LGFX_Sprite sprite17(&sprite1); //

static LGFX_Sprite spriteb[13];

void drawbuttonfx(){
  for(int i=10; i<13; i++){
  spriteb[i].createSprite(27,27);
  spriteb[i].fillScreen(BG);
  spriteb[i].fillCircle(13,13,8,C1);
  spriteb[i].fillArc(13,13,10,13,0,360,C1);
  spriteb[i].pushSprite(&sprite1,93,yst + spc*(i-10));    
  }
}

void drawbutton(int bank, int sample){
for(int i=1; i<10; i++){
  spriteb[i].createSprite(27,27);
  spriteb[i].fillScreen(BG);
  spriteb[i].fillCircle(13,13,8,C1);
  spriteb[i].fillArc(13,13,10,13,0, retarc(bank, i), C1);
  if(sample == i){ //該当時
    spriteb[sample].fillArc(13,13,10,13,0, retarc(bank, i), C2);
    spriteb[sample].fillCircle(13,13,8,C2);
  }else if(sample == 0){ //無選択時 
    spriteb[i].fillCircle(13,13,8,C1);
    spriteb[i].fillArc(13,13,10,13,0, retarc(bank,i), C1);
  }else{     
    spriteb[i].fillArc(13,13,10,13,0, retarc(bank,i), C1); 
  }
  if(0<i && i<4)spriteb[i].pushSprite(&sprite1, xst + spc*(i-1), yst); //(0,1,2)
  if(3<i && i<7)spriteb[i].pushSprite(&sprite1, xst + spc*(i-4), yst + spc); 
  if(6<i && i<10)spriteb[i].pushSprite(&sprite1, xst + spc*(i-7), yst + 2*spc); 
}
drawbuttonfx(); 
}

void drawbuttonvol(int bank, int sample, int vol){
for(int i=1; i<10; i++){
  spriteb[i].createSprite(27,27);
  spriteb[i].fillScreen(BG);
  spriteb[i].fillCircle(13,13,8,C1);
  //spriteb[i].fillArc(13,13,10,13,0, retarc(bank, i), C1);
  if(sample == i){ //該当時
    spriteb[sample].fillArc(13,13,10,13,0, vol, C2);
    spriteb[sample].fillCircle(13,13,8,C2);
  }else if(sample == 0){ //無選択時 
    spriteb[i].fillCircle(13,13,8,C1);
    spriteb[i].fillArc(13,13,10,13,0, retarc(bank,i), C1);
  }else{     
    spriteb[i].fillArc(13,13,10,13,0, retarc(bank,i), C1); 
  }
  if(0<i && i<4)spriteb[i].pushSprite(&sprite1, xst + spc*(i-1), yst); //(0,1,2)
  if(3<i && i<7)spriteb[i].pushSprite(&sprite1, xst + spc*(i-4), yst + spc); 
  if(6<i && i<10)spriteb[i].pushSprite(&sprite1, xst + spc*(i-7), yst + 2*spc); 
}
drawbuttonfx(); 
}



/*
void drawbutton_onokosi(int bank, int sample, int volume){
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
*/



/*
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
*/

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