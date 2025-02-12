void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(8,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,HIGH);
  delay (2000);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  delay (2000);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  delay (2000);
  digitalWrite(8,HIGH);
  digitalWrite(12,LOW);
  delay (2000);
  digitalWrite(8,LOW);
  digitalWrite(13,HIGH);

}
  
 

