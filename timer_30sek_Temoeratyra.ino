#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// линия данных подключена к цифровому выводу 2 Arduino
#define ONE_WIRE_BUS 2

SimpleTimer timer; // Создаём экземпляр класса для управления таймером

// настройка объекта oneWire для связи с любым устройством OneWire
OneWire oneWire(ONE_WIRE_BUS);  

// передать ссылку на oneWire библиотеке DallasTemperature
DallasTemperature sensors(&oneWire);

void Temperatur() {
  sensors.requestTemperatures(); 
  //Serial.print("Temperature(°C):"); Serial.print(sensors.getTempCByIndex(0)); Serial.print(" ");
    //Serial.print("Temperature: "); 
    Serial.print(sensors.getTempCByIndex(0)); Serial.print("°C"); Serial.print(" ");
    
    Serial.println();
}

void setup(void)
{ 
  sensors.begin();  // запустить библиотеку
  Serial.begin(9600);
  Serial.println("Temperature (sensor readings for every 30 seconds):");
  timer.setInterval(30000, Temperatur);// устанавливаем интервал в 1000мс (1 секунду)
}

void loop(void)
{ 
  timer.run(); // Запускаем таймер 
  // отправить команду для получения температуры
  sensors.requestTemperatures(); 
    
  delay(100);
}