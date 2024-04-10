/*
   Autor: Edgar Cano
   Rev: 10/04/2024   
 * Note:   Se utilizo la librería  <VL53L0X.h> en vez de "Adafruit_VL53L0X.h"
 *            por conflicto detectado con la libreria <Adafruit_SSD1306.h>, ya que 
 *            no se visualiza nada en la OLED.  
 */
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "RTClib.h"
#include <VL53L0X.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
//#define OLED_RESET      4
#define OLED_RESET LED_BUILTIN

Adafruit_SSD1306 oled(128, 64);  // declara la resolucion del display
VL53L0X sensor;
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(){
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  delay(100);  // se da una espera de 100ms para que el display inicie correctamente
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicia la comunicacion I2C con el display que tiene la direccion 0x3C
  oled.setRotation(0);  // se escoje la orientacion del display puede ser 0, 1, 2 o 3
  oled.setTextColor(WHITE);  // se le dice a la pantalla que el texto que se va a desplegar es en color blanco 
  oled.clearDisplay();
  oled.display();  

/* TEST OLED */
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);    
  oled.setCursor(35,0);          //(width=128, high=64)  
  oled.println("Test OLED"); 
  oled.setTextSize(2);    
  oled.setCursor(30,18);        //(width=128, high=64)  
  oled.println("SCREEN"); 
  oled.setTextSize(3);    
  oled.setCursor(10,40);        //(width=128, high=64)  
  oled.println("128x64"); 
  oled.display();    
  delay(2000); 
   
}

void loop(){
  int measure = sensor.readRangeContinuousMillimeters(); 
  
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

  if (measure != 4) {  // phase failures have incorrect data
    oled.clearDisplay();
    oled.setCursor(0,0);
    oled.print(measure);
    oled.print("mm");
    oled.display();
    Serial.println();
    delay(50);    
    Serial.print("Distance (mm): "); 
    Serial.print(measure);    
  } else {
    Serial.println(" out of range ");
    oled.display();
    oled.clearDisplay();
    return;
  }    
  delay(100); 
}




  
