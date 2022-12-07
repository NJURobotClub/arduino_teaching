#include <SPI.h>
#include "Adafruit_NeoPixel.h"    //引入头文件
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    4     //定义信号输出引脚
#define LED_COUNT 18     //定义LED灯个数  
#define ADD true
#define SUB false
#define R1 5
#define R2 6

//RED 0
//ORANGE 10
//YELLO 30
//GREEN 80 
//BLUE 120
//DARKBLUE 150
//PURPLE 190

boolean stat1 = true;     //呼吸状态反转标志
int val = 100;            //呼吸亮度变量
int color = 0;            //色彩改变变量
int count = 0;            //灯珠熄灭时间控制
int temp=0;
int temp2=-1;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);//创建灯条对象
uint32_t hsvcolor = strip.ColorHSV(0*256,255, val); //控制颜色

void tail(int);

void setup(){
  Serial.begin(9600);
  strip.begin();           
  //strip.show();

}

void loop(void){
  /*if(temp2>0)              //变色呼吸
  {
    temp=temp+20;
    temp2=-temp2;
  }*/

 tail(80);

  //跑马灯
  //temp=temp+10;  
    
}

void tail(int sideColor){
  
  for(int i = 0; i < LED_COUNT; i ++){
    hsvcolor = strip.ColorHSV(sideColor*256, 255, val);
    //sideColor=sideColor+10;
    strip.setPixelColor(i, hsvcolor);
  }
/*
  //呼吸
  
  if(val>=90)
    stat1 = SUB;
  if(count > 0){
    stat1 = ADD;              
    count = 0;
    temp2=-temp2;
  }
  else if(val<=4){ 
    count ++;
    strip.show();
    return;
  }  
  */    
  strip.show();
/*
  //呼吸
 delay(30);
 if(stat1==SUB) val -= 5;                
 else if(stat1==ADD) val += 5;  
 */
}
