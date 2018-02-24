/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include <dht.h>

#define pinUmi 2
#define pinLuz 1
#define pinTemp 0

float temperatura = 0.0;
int   leituraLuz  = 0;
int   iluminancia = 0;

//VARIÁVEIS CALIBRAÇÃO LUZ
const long A  = 1000;     //Resistência em oscuridão em KΩ
const int  B  = 15;       //Resistência à luz (10 Lux) em KΩ
const int  Rc = 10;       //Resistência de calibração em KΩ

//VARIÁVEIS SENSOR UMIDADE
dht      DHT;             //criar um objeto da classe DHT
uint32_t timer = 0;       // para leitura a cada 2s(tempo minimo leitura sensor)


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:rar files linux
  Serial.begin(9600);
  
  pinMode(pinTemp, INPUT);
  pinMode(pinLuz,  INPUT);
  pinMode(pinUmi,  INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(pinTemp);
  leituraLuz      = analogRead(pinLuz); 
  
  temperatura = ((float (sensorValue*5)/1023))/0.01;
  //ILUMINÂNCIA 
  iluminancia = ((long)leituraLuz*A*10)/((long)B*Rc*(1024-leituraLuz));

 //UMIDADE
  if(millis() - timer >= 5000)      // o sensor faz uma leitura a cada 5s
  {
    DHT.read22(A2);                 // chama método de leitura da classe dht,com o pino de transmissão de dados ligado no pino A2
    // print out the value you read:
    Serial.println("{\"T\":"+ String(temperatura) +",\"L\":" + String(iluminancia) + ",\"U\":" + String(DHT.humidity) + "}");
    timer = millis();
  }
   
  delay(1000);        // delay in between reads for stability
}
