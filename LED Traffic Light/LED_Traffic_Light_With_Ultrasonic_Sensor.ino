
#include <Arduino.h> // Inclui a biblioteca padrão do Arduino

/* Simular um cruzamento com dois semáforos usando uma máquina de estados */

#define TRIG 13   // Pino Trigger no pino 7 do Arduino
#define ECHO 12   // Pino Echo no pino 6 do Arduino

enum States {
  NORMAL, DETECTADO
};

States estado = NORMAL;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

  /* Semáforo 2 */
  pinMode(10, OUTPUT); // Vermelho Semáforo 2
  pinMode(9, OUTPUT); // Amarelo Semáforo 2
  pinMode(8, OUTPUT); // Verde Semáforo 2

  /* Semáforo 1 */
  pinMode(5, OUTPUT); // Vermelho Semáforo 1
  pinMode(6, OUTPUT);  // Amarelo Semáforo 1
  pinMode(7, OUTPUT);  // Verde Semáforo 1
}

long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  long duracao = pulseIn(ECHO, HIGH);
  long distancia = duracao * 0.034 / 1; // Converter para cm
  
  return distancia;
}

void loop() {
  long distancia = medirDistancia();
  Serial.println(distancia);

  switch (estado) {
    case NORMAL:
      // Estado inicial
      digitalWrite(TRIG, HIGH);
      digitalWrite(7, HIGH); 
      digitalWrite(10, HIGH); 
      if (distancia > 0 && distancia < 20) {
        estado = DETECTADO;
      }
      break;

    case DETECTADO:
      digitalWrite(TRIG, LOW);
      digitalWrite(7, LOW);    // Desliga o verde Semáforo 1
      digitalWrite(6, HIGH);   // Acende o amarelo Semáforo 1
      delay(2000);

      digitalWrite(6, LOW);    // Desliga o amarelo Semáforo 1
      digitalWrite(5, HIGH);  // Acende o vermelho Semáforo 1
      delay(2000);

      digitalWrite(10, LOW);   // Desliga o vermelho Semáforo 2
      digitalWrite(8, HIGH);  // Acende o verde Semáforo 2
      delay(15000);
      

      digitalWrite(8, LOW);   // Desliga o verde Semáforo 2
      digitalWrite(9, HIGH);  // Acende o amarelo Semáforo 2
      delay(2000);

      digitalWrite(9, LOW);   // Desliga o amarelo Semáforo 2
      digitalWrite(10, HIGH);  // Acende o vermelho Semáforo 2
      delay(2000);

      digitalWrite(5, LOW);   // Desliga o vermelho Semáforo 1
      digitalWrite(7, HIGH);   // Acende o verde Semáforo 1
      delay(2000);

      estado = NORMAL;
      break;
  }
}