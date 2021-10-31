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

//Smoothing
const int numReadings = 5;
int readingsA0[numReadings];      // the readings from the analog input
int readIndexA0 = 0;              // the index of the current reading
int totalA0 = 0;                  // the running total
int averageA0 = 0;                // the average
int readingsA1[numReadings];      // the readings from the analog input
int readIndexA1 = 0;              // the index of the current reading
int totalA1 = 0;                  // the running total
int averageA1 = 0;                // the average

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
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readingsA0[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readingsA1[thisReading] = 0;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //dataInputLeft = analogRead(inputShortLeft);
  //dataInputRight = analogRead(inputShortRight);

  // subtract the last reading:
  totalA0 = totalA0 - readingsA0[readIndexA0];
  totalA1 = totalA1 - readingsA1[readIndexA1];
  // read from the sensor:
  readingsA0[readIndexA0] = analogRead(inputShortLeft);
  readingsA1[readIndexA1] = analogRead(inputShortRight);
  // add the reading to the total:
  totalA0 = totalA0 + readingsA0[readIndexA0];
  totalA1 = totalA1 + readingsA1[readIndexA1];
  // advance to the next position in the array:
  readIndexA0 = readIndexA0 + 1;
  readIndexA1 = readIndexA1 + 1;

  // if we're at the end of the array...
  if (readIndexA0 >= numReadings) {
    // ...wrap around to the beginning:
    readIndexA0 = 0;
  }
  if (readIndexA1 >= numReadings) {
    // ...wrap around to the beginning:
    readIndexA1 = 0;
  }

  // calculate the average:
  dataInputLeft = averageA0 = totalA0 / numReadings;
  dataInputRight = averageA1 = totalA1 / numReadings;

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
  delay(1);
  
}
