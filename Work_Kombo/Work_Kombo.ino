#include <OneWire.h>

#include <DallasTemperature.h>

#include <Wire.h> // подключаем I2C библиотеку
#define addr 0x1E // I2C 7-битный адрес датчика HMC5883
// линия данных подключена к цифровому выводу 2 Arduino
#define ONE_WIRE_BUS 2

// настройка объекта oneWire для связи с любым устройством OneWire
OneWire oneWire(ONE_WIRE_BUS);  

// передать ссылку на oneWire библиотеке DallasTemperature
DallasTemperature sensors(&oneWire);

void setup() {
  sensors.begin();  // запустить библиотеку 
    Serial.begin(9600); // инициализация последовательного порта 
    Wire.begin(); // инициализация I2C
  
    // Задаём режим работы датчика HMC5883:
    Wire.beginTransmission(addr);
    Wire.write(0x00); // выбираем регистр управления CRA (00)
    Wire.write(0x70); // записываем в него 0x70 [усреднение по 8 точкам, 15 Гц, нормальные измерения]
    Wire.write(0xA0); // записываем в регистр CRB (01) 0xA0 [чувствительность = 5]
    Wire.write(0x00); // записываем в регистр Mode (02) 0x00 [бесконечный режим измерения]
    Wire.endTransmission();
}

void loop() { 
  // отправить команду для получения температуры
  sensors.requestTemperatures(); 

  // напечатать температуру в градусах Цельсия
  //Serial.print("Temperature: ");
  //Serial.print(sensors.getTempCByIndex(0));
  //Serial.print("°");// напечатать символ градусов
  //Serial.print("C  |  ");
  
  // напечатать температуру в градусах Фаренгейта
  //Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  //Serial.print("°");// напечатать символ градусов
  //Serial.println("F");
  
  Wire.beginTransmission(addr);
  Wire.write(0x03); // переходим к регистру 0x03
  Wire.endTransmission();
  
  Wire.requestFrom(addr, 6); // запрашиваем 6 байтов
  while( Wire.available() )  
  { 
    int h = Wire.read(); // старший байт значения по оси X
    int l = Wire.read(); // младший байт значения по оси X
    int x = word(h, l);  // объединяем в двухбайтовое число

    int y = Wire.read(); // старший байт значения по оси Y
    y = y << 8; // сдвигаем влево на 8 битов
    y = y | Wire.read(); // объединяем с младшим байтом по OR

    int z = Wire.read(); // старший байт значения по оси Z
    z = z << 8; // сдвигаем влево на 8 битов
    z = z | Wire.read(); // объединяем с младшим байтом по OR

    //*Serial.print("X = ");  
   // Serial.print(x, DEC);
    //Serial.print(" "); 
    //Serial.print("Y = ");  
    //Serial.print(y, DEC);
    //Serial.print(" "); 
    //Serial.print("Z = ");  
    //Serial.print(z, DEC); 
    //Serial.println();
    Serial.print("X:"); Serial.print(x); Serial.print(" ");
    Serial.print("Y:"); Serial.print(y); Serial.print(" ");
    Serial.print("Z:"); Serial.print(z); Serial.print(" ");
    Serial.print("Temperature(°C):"); Serial.print(sensors.getTempCByIndex(0)); Serial.print(" ");
    //Serial.print("Temperature: "); 
    Serial.print(sensors.getTempCByIndex(0)); Serial.print("°C"); Serial.print(" ");
    
    Serial.println();
    
  }
    delay(100);
}