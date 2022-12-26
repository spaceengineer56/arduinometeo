int pieza = 9;
int a = 0;
int b = 0;
#include "DHT.h"
#define DHTPIN 2 // Тот самый номер пина, о котором упоминалось выше
#include <Adafruit_GFX.h>        //OLED библиотека
#include <Adafruit_SSD1306.h>
#include <Wire.h>                //Библиотека I2C
#define SCREEN_WIDTH 128 // Ширина OLED-дисплея, в пикселях
#define SCREEN_HEIGHT 32 // Высота OLED-дисплея в пикселях
#define OLED_RESET    -1 // т.к.у дисплея нет пина сброса прописываем -1, если используется общий сброс Arduino
DHT dht(DHTPIN, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Объявляем имя и задаем параметры
void setup() {
  pinMode(pieza, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Запуск дисплея
  display.display();
  delay(2000);            
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  delay(100);
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    Serial.println("Ошибка считывания");
    return;
  }
   display.clearDisplay();               //Очистить дисплей
    display.setTextSize(1);               //Задаем размер текста
    display.setTextColor(WHITE);          //Задаем цвет текста
    display.setCursor(0,0);             //Задаем координату начала текста в пикселях
    display.print("temp: ");  
    display.print(t);  
    display.println("C");
    display.print("humidity: ");  
    display.print(h);
    display.println("%"); 
    if ((t > 19 and t <= 28) and (h > 30 and h < 60)) {;
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      display.println("normal");
      a = 0; 
      if (b == 0) {
      analogWrite(pieza, 170);
      delay(50);
      analogWrite(pieza, 0);
      delay(100);
      analogWrite(pieza, 170);
      delay(50);
      analogWrite(pieza, 0);
      delay(100);
      b = 1;
      }
    }
    else{
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      display.println("not normal");
      b = 0;
      if (a == 0) {
      analogWrite(pieza, 100);
      delay(150);
      analogWrite(pieza, 0);
      delay(200);
      analogWrite(pieza, 100);
      delay(150);
      analogWrite(pieza, 0);
      delay(200);
      analogWrite(pieza, 100);
      delay(150);
      analogWrite(pieza, 0);
      delay(200);
      a = 1;
      }
    }
    display.display();  //Команда для отображения всего этого на дисплее
}
