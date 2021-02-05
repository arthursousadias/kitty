/*******************************************************************
 * Objetivo : Projeto de um pequeno carrinho controlado pelo Arduino
 * através de um celular utilizando um APP em java.
 * Desenvolvido por : Arthur Dias
 * Data de início : 04/02/2021
 * *****************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>
int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int servoPin = 5;
int luzesPin = 9;
bool luzes = false;
Servo servo;

/***Protótipos as funções***/
void escrever();
void frente();
void re();
void esquerda();
void direita();
void freio();
void controleServo(int graus);
void acenderLuzes();

void setup()
{
  servo.attach(servoPin);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(luzesPin, OUTPUT);
}

void loop()
{  
  escrever();
}

void escrever()
{
  char c;
  c = Serial.read();
  while (c > 0)
  {
    if (c != '-')
    {
      switch (c)
      {
      case '1':
        frente();
        controleServo(90);
        Serial.println("Frente");
        break;
      case '2':
        controleServo(90);
        re();
        Serial.println("ré");
        break;
      case '3':
        direita();
        controleServo(20);
        Serial.println("direita");
        break;
      case '4':
       controleServo(160);
        esquerda();
        Serial.println("esquerda");
        break;
      case '5':
        acenderLuzes();
        break;
      case '6':
        freio();
        Serial.println("freio");
        break;
      }        
    }
    c = Serial.read();
  }
}
void re()
{
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //Gira o Motor B no sentido horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void frente()
{
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Gira o Motor B no sentido anti-horario
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void direita()
{
  //Para o motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda()
{
  //Para o motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void freio()
{
  //Para o motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  //Para o motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void acenderLuzes() {
  if (!luzes)
  {
    /* Acende a luz */
    Serial.println("Luz Acessa");
    digitalWrite(luzesPin, HIGH);
    luzes = true;
  }else{
    Serial.println("Luz Apagada");
    luzes = false;
    digitalWrite(luzesPin, LOW);
  }  
}

void controleServo(int graus){
  servo.write(graus);
}
