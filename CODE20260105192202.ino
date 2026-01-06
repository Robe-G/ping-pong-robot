#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//LIBRERIA PARA CONTROL BT DABBLE
#include <Dabble.h>

#include <Servo.h>

Servo miServo;

#define dirMotorIa 22
#define dirMotorIb 23
#define velocidadMI 2
#define dirMotorDa 24
#define dirMotorDb 25
#define velocidadMD 3
//#define potenciometroAA A15
//#define potenciometroID A14 
//#define ledMotorI 11
#define LedIndicador 12

int velMotorIzq=0;
int velMotorDer=0;

int xAxisInt=0;
int yAxisInt=0;

int posicionServo=0;

long adelanteAtras=0;
long izquierdaDerecha=0;

unsigned long tiempoAnterior=0;
unsigned long tiempoActual=0;

void setup() {
  pinMode(dirMotorIa,OUTPUT);
  pinMode(dirMotorIb,OUTPUT);
  pinMode(velocidadMI,OUTPUT);
  pinMode(dirMotorDa,OUTPUT);
  pinMode(dirMotorDb,OUTPUT);
  pinMode(velocidadMD,OUTPUT);
 // pinMode(potenciometroAA,INPUT);
  //pinMode(potenciometroID,INPUT);
  //pinMode(ledMotorI,OUTPUT);
  pinMode(LedIndicador,OUTPUT);

  miServo.attach(5);
  miServo.write(90);

  Dabble.begin(9600);
  tiempoAnterior=millis();
}
void moverMotor(int dirIzqA, int dirIzqB, int dirDerA, int dirDerB, int velMotIzq, int velMotDer){ 
  //analogWrite(ledMotorI, velmotI); 
  //analogWrite(ledMotorD, velmotD); 
  digitalWrite(dirMotorIa,dirIzqA); 
  digitalWrite(dirMotorIb,dirIzqB); 
  analogWrite(velocidadMI,velMotIzq); 
  digitalWrite(dirMotorDa,dirDerA); 
  digitalWrite(dirMotorDb,dirDerB); 
  analogWrite(velocidadMD,velMotDer); 
  }

void loop() {
  Dabble.processInput();
  yAxisInt=int(100*GamePad.getYaxisData());
  xAxisInt=int(100*GamePad.getXaxisData());
  adelanteAtras=map(yAxisInt,-700,700,-255,255);
  izquierdaDerecha=map(xAxisInt,-700,700,-255,255);
  if (GamePad.isTrianglePressed()){
    tiempoActual=millis()-tiempoAnterior;
    if (tiempoActual>5){
      posicionServo--;
      tiempoAnterior=millis();
    }
    if (posicionServo>0){
      miServo.write(posicionServo);
    } 
    else {
      posicionServo=0;
    }
  }
  if (GamePad.isCrossPressed()){
    tiempoActual=millis()-tiempoAnterior;
    if (tiempoActual>5){
      posicionServo++;
      tiempoAnterior=millis();
    }
    if (posicionServo<180){
      miServo.write(posicionServo);
    } 
    else{
      posicionServo=180;
    }
  }

  if (adelanteAtras>5 & izquierdaDerecha>5){
    velMotorIzq=map(adelanteAtras,5,255,50,255);
    velMotorDer=map(izquierdaDerecha,5,255,velMotorIzq,0);
    moverMotor(1,0,1,0,velMotorIzq,velMotorDer);
  }
  else if (adelanteAtras>5 & izquierdaDerecha<-5){
    velMotorDer=map(adelanteAtras,5,255,50,155);
    velMotorIzq=map(izquierdaDerecha,-5,-255,velMotorDer,0);
    moverMotor(1,0,1,0,velMotorIzq,velMotorDer);
  }
  else if (adelanteAtras<-5 & izquierdaDerecha>5){
    velMotorIzq=map(adelanteAtras,-5,-255,50,255);
    velMotorDer=map(izquierdaDerecha,5,255,velMotorIzq,0);
    moverMotor(0,1,0,1,velMotorIzq,velMotorDer);
  }
  else if (adelanteAtras<-5 & izquierdaDerecha<-5) {
    velMotorDer=map(adelanteAtras,-5,255,50,255);
    velMotorIzq=map(izquierdaDerecha,-5,-255,velMotorDer,0);
    moverMotor(0,1,0,1,velMotorIzq,velMotorDer);
  }
  else if (adelanteAtras>5) {
    velMotorIzq=map(adelanteAtras,5,255,50,255);
    velMotorDer=velMotorIzq;
    moverMotor(1,0,1,0,velMotorIzq,velMotorDer);
  }
  else if (adelanteAtras < -5) {
    velMotorIzq=map(adelanteAtras,-5,-255,50,255);
    velMotorDer=velMotorIzq;
    moverMotor(0,1,0,1,velMotorIzq,velMotorDer);
  }
  else if (izquierdaDerecha>5) {
    velMotorIzq=map(izquierdaDerecha,5,255,50,255);
    velMotorDer=velMotorIzq;
    moverMotor(1,0,0,1,velMotorIzq,velMotorDer);
  }
  else if(izquierdaDerecha<-5) {
    velMotorDer=map(izquierdaDerecha,-5,-255,50,255);
    velMotorIzq=velMotorDer;
    moverMotor(0,1,1,0,velMotorIzq,velMotorDer);
  }
  else{
    moverMotor(0,0,0,0,0,0);
  }
}