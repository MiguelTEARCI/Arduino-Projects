#include <Arduino.h>
#include <Stepper.h>

int int1 = 7;
int int2 = 6;
int int3 = 5;
int int4 = 4;

int counterClockwise = 13;
int clockwise = 12;

int pole1[] = {0,0,0,0,0,1,1,1,0};
int pole2[] = {0,0,0,1,1,1,0,0,0};
int pole3[] = {0,1,1,1,0,0,0,0,0};
int pole4[] = {1,1,0,0,0,0,0,1,0};

int counter1 = 0;
int counter2 = 0;

int dir = 3;
int poleStep = 0;


void driverStepper(int step);

void setup() {
  pinMode (int1,OUTPUT);
  pinMode (int2,OUTPUT);
  pinMode (int3,OUTPUT);
  pinMode (int4,OUTPUT);

  pinMode(counterClockwise,INPUT_PULLUP);
  pinMode(clockwise,INPUT_PULLUP);
}

void loop() {
  int btn1State = digitalRead(counterClockwise);
  int btn2State = digitalRead(clockwise);

  if (btn1State == LOW) {
    counter1++;
    delay(500);
    if (counter1 != 2) {
      counter2 = 0;
      dir = 1;
    } else {
      counter1 = 0;
      dir = 3;
    }    
  }

  if (btn2State == LOW) {
    counter2++;
    delay(500);
    if (counter2 != 2) {
      counter1 = 0;
      dir = 2;
    } else {
      counter2 = 0;
      dir = 3;
    }
  }

  if (dir == 1) {
    poleStep++;
    driverStepper(poleStep);
  } else if (dir == 2) {
    poleStep--;
    driverStepper(poleStep);
  } else {
    driverStepper(8);
  }

  if (poleStep > 7) {
    poleStep = 0;
  } else if (poleStep < 0) {
    poleStep = 7;
  }
  
  delay(1);
}

void driverStepper(int step) {
  digitalWrite(int1, pole1[step]);
  digitalWrite(int2, pole2[step]);
  digitalWrite(int3, pole3[step]);
  digitalWrite(int4, pole4[step]);
}
