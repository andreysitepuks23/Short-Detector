#define inputShortLeft A0
#define inputShortRight A1
#define buzzer 2
#define ledLeft 3
#define ledRight 4
#define LED 13
#define controlWireClampStart 5

int dataInputLeft, dataInputRight;
int tresholdValue = 30;
int tresholdpluged = 200; //unpluged = 1023

void setup() {
  Serial.begin(9600);
  pinMode(inputShortLeft,INPUT_PULLUP);
  pinMode(inputShortRight,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  pinMode(ledLeft,OUTPUT);
  pinMode(ledRight,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(controlWireClampStart,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  dataInputLeft = analogRead(inputShortLeft);
  dataInputRight = analogRead(inputShortRight);

  if(dataInputLeft < tresholdValue){
    digitalWrite(ledLeft,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(controlWireClampStart,HIGH);
    
  }

  else if(dataInputRight < tresholdValue){
    digitalWrite(ledRight,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(controlWireClampStart,HIGH);
  }
  else{
    digitalWrite(ledRight,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(ledLeft,LOW);
    digitalWrite(buzzer,LOW);
    if (dataInputLeft > tresholdpluged && dataInputRight > tresholdpluged){
      digitalWrite(controlWireClampStart,HIGH);
    }
    else {
      digitalWrite(controlWireClampStart,LOW);
    }
  }


//  Serial.print("Data Left :\t");
//  Serial.print(dataInputLeft);
//  Serial.print("\tData Right :\t");
//  Serial.println(dataInputRight);
  digitalWrite(LED, HIGH);
  
}
