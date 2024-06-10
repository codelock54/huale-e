#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);

//leds
//int pindVerde = 4; 
//int pinRojo = 2; 
bool encender = true;
// pines 3,5,6,9 probamos que llanta se mueve
int salida = 4; //atras
int salida2 = 5;//adelante
int salida3 = 6;//con esto se mueve el motor (out1,out2) rota antihoraria --> hacia atras
int salida4 = 8;
int i = 9;
int d = 3;//se mueve el motor (out1,out2) rota horaria --> hacia adelante
//valores capturados del Bluetooth

int sensorIzquierda = A0;
int sensorDerecha = A1;

char senial;
void setup() {

  // para la conexion de bluetooth
  BT.begin(115200);
  Serial.begin(9600);
  //=================
}

bool detectarNegroIzquierdo() {
  int sensor = analogRead(sensorIzquierda);
  Serial.print("Sensor Izquierdo : ");
  Serial.println( sensor);
  // Mas de 500 significa que es negro
  return (sensor > 500);

}

bool detectarNegroDerecho() {
  int sensor1 = analogRead(sensorDerecha);
  // Mas de 500 significa que es negro
  Serial.print("Sensor Derecho : ");
  Serial.println(sensor1);
  return (sensor1 > 500);
}



void decision() {
  bool estadoI = detectarNegroIzquierdo();
  bool estadoD = detectarNegroDerecho();
  if (estadoI && estadoD){
    Alfrente();
  }else{
    if (estadoI){
      Izquierda();
    }else if(estadoD){
      Derecha();
    }else{
      Izquierda();
    }
  }
}

void loop() {
  conexionBluetooth();
  //Alfrente();
  //decision();
  delay(100);
//======================================================
}

void conexionBluetooth(){
  //===========================DATOS CAPTURADOS DE LA SEÑAL BLUETOOTH
  if(BT.available())
    senial = BT.read();
    Serial.println(senial);

 
  switch (senial)
  {
    case 'w':
      Alfrente();
      break;

    case 's':
      Atras();
      break;

    case 'd':
      Derecha();
      break;

    case 'a':
      Izquierda();
      break;
    case 'c':
      encender = true;
      break;
  }

   if(BT.available()){
    Serial.write(BT.read());
  }
  if(Serial.available()){
    BT.write(Serial.read());
  }
}

void Alfrente(){
  analogWrite(salida,250); //al 50% max 255 100%
  analogWrite(salida4,250);
}

void Derecha(){
  digitalWrite(salida,250); //al 50% max 255 100%
  digitalWrite(salida3,250);
}

void Izquierda(){
  digitalWrite(salida4,250); //al 50% max 255 100%
  digitalWrite(salida2,250);
}

void Atras(){
  digitalWrite(salida2,250); //al 50% max 255 100%
  digitalWrite(salida3,250);
}

void detener(){
  digitalWrite(salida3,0); //señal pwm al 0%
  digitalWrite(salida4,0); //señal pwm al 0%
  digitalWrite(salida,0); //señal pwm al 0%
  digitalWrite(salida2,0);//señal pwm al 0%
}