#include <Arduino.h>

const int RED = 7;
const int GREEN = 6;
const int BLUE = 5;
const int Botao = 4;
const int Sensor = A0;

int Botao_Estado = 0;


void setup() {
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
  pinMode (Botao, INPUT);
  pinMode (Sensor,INPUT);
}

void loop() {
  int Valor_Luz = analogRead(Sensor);
  Serial.print ("Valor_Luz: ");
  Serial.println(Valor_Luz);
  int luminosidade = map (Valor_Luz, 25, 1023, 0, 255);

  analogWrite (RED,luminosidade);
  
  

  delay (0);
  
  Botao_Estado = digitalRead (Botao);
  if (Botao_Estado== HIGH) {
    digitalWrite (RED, HIGH);
    digitalWrite (GREEN, HIGH);
    digitalWrite (BLUE, LOW);

  } else{
    digitalWrite (RED, LOW);
    digitalWrite (GREEN, LOW);
    digitalWrite (BLUE, LOW);
  }



}
    
    
    

