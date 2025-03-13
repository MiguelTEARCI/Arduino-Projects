#include <Arduino.h>
#include <Stepper.h>

// Definição dos pinos dos motores
int motor1_pins[] = {10, 11, 12, 13};  // Motor 1
int motor2_pins[] = {6, 7, 8, 9};      // Motor 2

// Definição dos botões (sensores)
int sensor1 = 2;  // Botão 1 (motor 1 começa a rodar)
int sensor2 = 3;  // Botão 2 (conta peças com motor 2)

// Sequência de passos do motor de passo
int stepSequence[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

// Variáveis de controle
bool motor1On = false;         // Motor 1 ligado
bool motor2On = false;         // Motor 2 ligado
int pieceCount = 0;            // Contador de peças
int stepIndex1 = 0;            // Passo atual do motor 1
int stepIndex2 = 0;            // Passo atual do motor 2
unsigned long lastStepTime1 = 0;  // Último tempo de passo do motor 1
unsigned long lastStepTime2 = 0;  // Último tempo de passo do motor 2
unsigned long stepDelay = 5;  // Tempo entre passos do motor

unsigned long motor2StopTime = 0;  // Tempo para o motor 2 parar após 5 segundos
bool motor2DelayedStop = false;    // Flag para controlar a parada do motor 2
bool motor1Stopped = false;        // Flag para verificar se o motor 1 já foi parado

void stepMotor(int motorPins[], int step);

void setup() {
    // Configuração dos pinos dos motores como saída
    for (int i = 0; i < 4; i++) {
        pinMode(motor1_pins[i], OUTPUT);
        pinMode(motor2_pins[i], OUTPUT);
    }

    // Configuração dos botões como entrada com pull-up
    pinMode(sensor1, INPUT_PULLUP);
    pinMode(sensor2, INPUT_PULLUP);

    // Inicia a comunicação serial
    Serial.begin(9600);
    Serial.println("Sistema iniciado. À espera de peça...");
}

void loop() {
    unsigned long currentTime = millis();

    // Pressionar o sensor 1 inicia o motor 1 (se ainda estiver desligado)
    if (digitalRead(sensor1) == LOW && !motor1On) {
        motor1On = true;
        Serial.println("Tapete 1 LIGADO.");
        delay(500);  // Debounce do botão
    }

    // Pressionar o sensor 2 inicia o motor 2 e conta as peças
    if (digitalRead(sensor2) == LOW && pieceCount < 10) {
        if (!motor2On) {
            motor2On = true;
            Serial.println("Tapete 2 LIGADO.");
        }
        pieceCount++;
        Serial.print("Peça confirmada! Contagem atual: ");
        Serial.println(pieceCount);
        delay(500);  // Debounce do botão
    }

    // Quando a contagem de peças chegar a 10, parar o motor 1 e aguardar 5 segundos para parar o motor 2
    if (pieceCount >= 10 && !motor1Stopped) {
        Serial.println("A caixa está cheia! A parar tapete...");
        motor1On = false;
        motor1Stopped = true;  // Marcar que o motor 1 já foi parado
        motor2DelayedStop = true;
        motor2StopTime = currentTime;
        Serial.println("Tapete 1 PARADO.");
    }

    // Após 5 segundos, parar o motor 2
    if (motor2DelayedStop && (currentTime - motor2StopTime >= 5000)) {
        motor2On = false;
        motor2DelayedStop = false;
        Serial.println("Tapete 2 PARADO.");
    }

    // Controle dos motores
    if (motor1On) {
        if (millis() - lastStepTime1 >= stepDelay) {
            lastStepTime1 = millis();
            stepMotor(motor1_pins, stepIndex1);
            stepIndex1 = (stepIndex1 + 1) % 4;
        }
    }

    if (motor2On) {
        if (millis() - lastStepTime2 >= stepDelay) {
            lastStepTime2 = millis();
            stepMotor(motor2_pins, stepIndex2);
            stepIndex2 = (stepIndex2 + 1) % 4;
        }
    }
}

// Função para controlar os motores
void stepMotor(int motorPins[], int step) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(motorPins[i], stepSequence[step][i]);
    }
}