/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christian/Documents/LiquidPrep/LightCommunication/src/LightCommunication.ino"
/*
 * Project LightCommunication
 * Description: Uses a NeoPixel to send soil moisture data via morse code to a mobile app
 * Author: Christian Chavez
 * Date: March 2021
 */

void setup();
void loop();
void sendMorse();
void dash();
void dot();
#line 8 "/Users/christian/Documents/LiquidPrep/LightCommunication/src/LightCommunication.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <neopixel.h>

#define PIXEL_PIN D2
#define PIXEL_COUNT 12
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int dashTime=300;
int dotTime=100;
int offTime=100;
unsigned int currentTime=millis();

int soilRead;
int mappedRead;
int soilPin=A2;
uint8_t i;
uint8_t n;
uint8_t soil[4];
uint8_t soilMapped[4];

void setup() {
  pinMode(soilPin, INPUT);
  pixel.begin();
  pixel.show();
  pixel.clear();
  pixel.setBrightness(20);
  currentTime=millis();
}

void loop() {
  if(millis()-currentTime>10000){
    soilRead=analogRead(soilPin);
    soil[0]=soilRead/1000; //calculations for accessing individual characters from soil reading
    soil[1]=((soilRead-(soil[0]*1000))/100);
    soil[2]=(soilRead-(soil[0]*1000)-(soil[1]*100))/10;
    soil[3]=(soilRead-(soil[0]*1000)-(soil[1]*100))%10;
    sendMorse();
    currentTime=millis();
  }
}
  
void sendMorse(){  //.-. / -.-.- <your message> .-.-. //format for sending messages
  dot(); //calibrate camera brightness
  dash();
  dot();
  delay(300);
  dash(); //gain camera attention
  dot();
  dash();
  dot();
  dash();
  delay(300);

  for(i=0;i<4;i++){
    Serial.printf("soil[i] = %i i = %i\n",soil[i],i);
    if(soil[i]==0){
      dash();
      dash();
      dash();
      dash();
      dash();
    }
    else if(soil[i]==1){
      dot();
      dash();
      dash();
      dash();
      dash();
    }
    else if(soil[i]==2){
      dot();
      dot();
      dash();
      dash();
      dash();
    }
    else if(soil[i]==3){
      dot();
      dot();
      dot();
      dash();
      dash();
    }
    else if(soil[i]==4){
      dot();
      dot();
      dot();
      dot();
      dash(); 
    }
    else if(soil[i]==5){
      dot();
      dot();
      dot();
      dot();
      dot();
    }
    else if(soil[i]==6){
      dash();
      dot();
      dot();
      dot();
      dot();
    }
    else if(soil[i]==7){
      dash();
      dash();
      dot();
      dot();
      dot();
    }
    else if(soil[i]==8){
      dash();
      dash();
      dash();
      dot();
      dot();
    }
    else if(soil[i]==9){
      dash();
      dash();
      dash();
      dash();
      dot();
    }
  delay(300);
  }
  dot(); //message over
  dash();
  dot();
  dash();
  dot();
  Serial.printf("Over\n");
}

void dash(){
  for(n=0;n<=12;n++){
   pixel.setPixelColor(n,255,255,255);
   pixel.show();
  }
  delay(dashTime);
  pixel.clear();
  pixel.show();
  delay(offTime);
}

void dot(){
  for(n=0;n<=12;n++){
    pixel.setPixelColor(n,255,255,255);
    pixel.show();
  }
  delay(dotTime);
  pixel.clear();
  pixel.show();
  delay(offTime);
}