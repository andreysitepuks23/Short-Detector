#define inputShortLeft A0
#define inputShortRight A1
#define buzzer 2
#define ledLeft 3
#define ledRight 4
#define LED 13
#define controlWireClampStart 5
//#define controlWireClampStart1 6

int dataInputLeft, dataInputRight;
int tresholdValue = 20;
int tresholdpluged = 165; //unpluged = 200

void setup() {
  Serial.begin(9600);
//  pinMode(inputShortLeft,INPUT_PULLUP); //Internal Pull-up 5V
//  pinMode(inputShortRight,INPUT_PULLUP); //Internal Pull-up 5V
  pinMode(inputShortLeft,INPUT); //External Pull-up 1V
  pinMode(inputShortRight,INPUT); //External Pull-up 1V
  pinMode(buzzer,OUTPUT);
  pinMode(ledLeft,OUTPUT);
  pinMode(ledRight,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(controlWireClampStart,OUTPUT);
  //pinMode(controlWireClampStart1,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  dataInputLeft = analogRead(inputShortLeft);
  dataInputRight = analogRead(inputShortRight);

  if(dataInputLeft < tresholdValue){
    digitalWrite(ledLeft,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(controlWireClampStart,LOW);
    //digitalWrite(controlWireClampStart1,LOW);
    
  }

  else if(dataInputRight < tresholdValue){
    digitalWrite(ledRight,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(controlWireClampStart,LOW);
    //digitalWrite(controlWireClampStart1,LOW);
  }
  else{
    digitalWrite(ledRight,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(ledLeft,LOW);
    digitalWrite(buzzer,LOW);
    if (dataInputLeft > tresholdpluged || dataInputRight > tresholdpluged){
      digitalWrite(controlWireClampStart,LOW);
      //digitalWrite(controlWireClampStart1,LOW);
    }
    else {
      digitalWrite(controlWireClampStart,HIGH);
      //digitalWrite(controlWireClampStart1,HIGH);
    }
  }


//  Serial.print("Data Left :\t");
//  Serial.print(dataInputLeft);
//  Serial.print("\tData Right :\t");
//  Serial.println(dataInputRight);
  digitalWrite(LED, HIGH);
  
}
