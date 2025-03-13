const int botao = 9; // Pino do botao
const int ledverde = 4; // Pino do ledverde
const int ledamarelo = 7;// Pino do ledamarelo
const int ledvermelho = 8;// Pino do ledvermelho


void setup(){
  Serial.begin(9600);
  pinMode(botao,INPUT); // Define botao como input
  pinMode(ledverde,OUTPUT); // Define o led como output
  pinMode(ledamarelo,OUTPUT);// // //
  pinMode(ledvermelho,OUTPUT);// // //
  

}

void loop(){
  int estadobotao = digitalRead(botao);
  
  if(estadobotao == HIGH){
    digitalWrite(ledverde,LOW);
    digitalWrite(ledamarelo,HIGH);
    delay(3000);
    digitalWrite(ledamarelo,LOW);
    digitalWrite(ledvermelho,HIGH);
    delay(2000);
    

  }else{
    digitalWrite(ledverde,HIGH);
    digitalWrite(ledamarelo,LOW);
    digitalWrite(ledvermelho,LOW);


  }

  delay(250);
  }
  


