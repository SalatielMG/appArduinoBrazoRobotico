#include <Servo.h>
#include <Separador.h>

Servo base, brazoDerecho, brazoIzquierdo, pinzas;
Separador s;

const int BASE = 1;
const int BRAZODERECHO = 2;
const int BRAZOIZQUIERDO = 3;
const int PINZA = 4;
const int PULSOMIN = 500;
const int PULSOMAX = 2500;

int pinBase = 2;
int pinBrazoDerecho = 3;
int pinBrazoIzquierdo = 4;
int pinPinzas = 5;
int dormir = 50;
int mov;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  
  base.attach(pinBase, PULSOMIN, PULSOMAX);
  brazoDerecho.attach(pinBrazoDerecho, PULSOMIN, PULSOMAX);
  brazoIzquierdo.attach(pinBrazoIzquierdo, PULSOMIN, PULSOMAX);
  pinzas.attach(pinPinzas, PULSOMIN, PULSOMAX);
  
  valorInicialServos();
  
}

void valorInicialServos() {
  base.write(90);
  brazoDerecho.write(90);
  brazoIzquierdo.write(90);
  pinzas.write(10);
}

void loop() {

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int num = Serial.read();
    
    movServo(num);

    /*String servo = s.separa(datosRecibidos, ',', 0);
      String anguloMinimo = s.separa(datosRecibidos, ',', 1);
      String anguloMaximo = s.separa(datosRecibidos, ',', 2);

      Serial.println("Dato recibido: " + datosRecibidos);
      Serial.println("servo: " + servo);
      Serial.println("anguloMinimo: " + anguloMinimo);
      Serial.println("anguloMaximo: " + anguloMaximo);

      moverServo(servo.toInt(), anguloMinimo.toInt(), anguloMaximo.toInt());*/
  }
}

void movServo(int num) {  
  if (num >= 0 && num < 63) {
    mov = map(num, 0, 62, 0, 180);
    base.write(mov);
  }
  if (num >= 63 && num < 126) {
    mov = map(num, 63, 125, 0, 180);
    brazoDerecho.write(mov);
  }
  if (num >= 126 && num <189) {
    mov = map(num, 126, 188, 0, 180);  
    brazoIzquierdo.write(mov);  
  }
  if (num >= 189 && num <252) {
    mov = map(num, 189, 251, 0, 180);   
    pinzas.write(mov); 
  }  
}
void moverServo(int servo, int anguloMinimo, int anguloMaximo) {
  switch (servo) {
    case BASE:
      if (anguloMinimo > anguloMaximo) {
        for (int i = anguloMinimo; i >= anguloMaximo; i --) {
          base.write(i);
          delay(dormir);
        }
      } else {
        for (int i = anguloMinimo; i <= anguloMaximo; i ++) {
          base.write(i);
          delay(dormir);
        }
      }
      break;
    case BRAZODERECHO:
      if (anguloMinimo > anguloMaximo) {
        for (int i = anguloMinimo; i >= anguloMaximo; i --) {
          brazoDerecho.write(i);
          delay(dormir);
        }
      } else {
        for (int i = anguloMinimo; i <= anguloMaximo; i ++) {
          brazoDerecho.write(i);
          delay(dormir);
        }
      }
      break;
    case BRAZOIZQUIERDO:
      if (anguloMinimo > anguloMaximo) { //
        for (int i = anguloMinimo; i >= anguloMaximo; i --) {
          brazoIzquierdo.write(i);
          delay(dormir);
        }
      } else { //
        for (int i = anguloMinimo; i <= anguloMaximo; i ++) {
          brazoIzquierdo.write(i);
          delay(dormir);
        }
      }
      break;
    case PINZA:
      pinzas.write(anguloMinimo);
      delay(dormir);
      /*if (anguloMinimo > anguloMaximo) { //Abre pinza
        for (int i = anguloMinimo; i >= anguloMaximo; i --) {
          pinzas.write(i);
          delay(dormir);
        }
        } else { // Cierra pinza
        for (int i = anguloMinimo; i <= anguloMaximo; i ++) {
          pinzas.write(i);
          delay(dormir);
        }
        }*/
      break;
    default:
      Serial.println("No se ejecuto nada");
      break;
  }

}
