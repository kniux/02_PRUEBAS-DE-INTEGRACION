/*
  Autor: Edgar Cano
  Rev: 10/04/2024   
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 8 

int buzzerPin = 12;

char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {33,35,37,39}; // Conectar a las salidas de fila del teclado.
byte colPins[COLS] = {41,43,45,47}; // Conectar a las salidas de columna del teclado.

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4);  

void setup(){
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); 
 Serial.println("Enter Password:");
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
 
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    Serial.print(Data[data_count]);    
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.setCursor(2,1);
      lcd.print("Correcto  ");
      Serial.println("Correcto");    
      digitalWrite(buzzerPin, HIGH); 
      delay(5000);
      digitalWrite(buzzerPin, LOW );
      }
    else{
      lcd.setCursor(2,1);
      lcd.print("Incorrecto");
     Serial.println("Incorrecto");    
      delay(1000);
      }    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
