#define signalStartButton 11
#define enableRelayA 10
#define enableRelayB 9
#define enableRelayC 8
#define enableRelayD 7
#define passLED 2
#define failLED 3
#define failBuzzer 4
#define signalOHMMultimeter A1
#define signalBuzzerMultimeter 5

int startButton = 0;
int sequence = 0;
int dataADC = 0;
int dataBuzzer = 0;
int durationPerSequence = 300; //total time 1 cycle is durationPerSequence x n (n = total Sequence)
int decisionDuration = 2000; //duration for the result
bool lockTime = false;
unsigned long startTime = 0;
int limitValue = 600;

//data Smoothing
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(signalStartButton, INPUT_PULLUP);
  pinMode(enableRelayA, OUTPUT);
  pinMode(enableRelayB, OUTPUT);
  pinMode(enableRelayC, OUTPUT);
  pinMode(enableRelayD, OUTPUT);
  pinMode(passLED, OUTPUT);
  pinMode(failLED, OUTPUT);
  pinMode(failBuzzer, OUTPUT);
  pinMode(signalOHMMultimeter, INPUT_PULLUP);
  pinMode(signalBuzzerMultimeter, INPUT_PULLUP);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  startButton = digitalRead(signalStartButton);
  dataBuzzer = digitalRead(signalBuzzerMultimeter);
  //dataADC = analogRead(signalOHMMultimeter);

    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(signalOHMMultimeter);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  dataADC = average;
  Serial.print("Data ADC : ");
  Serial.println(dataADC);
  switch(sequence){
    case 0: // Standby Case
      controlRelay(0,0,0,0);
      passTesting(0);
      failTesting(0);
      if (startButton == LOW){
        //digitalWrite(13,HIGH);
        sequence = 1;
      }
     break;
    case 1: //Check Pin 1-2
      controlRelay(0,0,0,0);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= durationPerSequence){
        //if(dataBuzzer == HIGH){
        if(dataADC < limitValue){
          sequence = 7;
          lockTime = false;
        }else{
          sequence = 2;
          lockTime = false;
        }
      }
        break;
    case 2: //Check Pin 2-3
      controlRelay(0,0,1,0);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= durationPerSequence){
        //if(dataBuzzer == HIGH){
        if(dataADC < limitValue){
          sequence = 7;
          lockTime = false;
        }else{
          sequence = 3;
          lockTime = false;
        }
      }
        break;
    case 3: //Check Pin 3-4
      controlRelay(1,0,1,0);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= durationPerSequence){
        //if(dataBuzzer == HIGH){
        if(dataADC < limitValue){
          sequence = 7;
          lockTime = false;
        }else{
          sequence = 4;
          lockTime = false;
        }
      }
        break;
    case 4: //Check Pin 4-5
      controlRelay(1,1,0,0);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= durationPerSequence){
        //if(dataBuzzer == HIGH){
         if(dataADC < limitValue){
          sequence = 7;
          lockTime = false;
        }else{
          sequence = 5;
          lockTime = false;
        }
      }
        break;
    case 5: //Check Pin 5-6
      controlRelay(1,1,0,1);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= durationPerSequence){
        //if(dataBuzzer == HIGH){
         if(dataADC < limitValue){
          sequence = 7;
          lockTime = false;
        }else{
          sequence = 6;
          lockTime = false;
        }
      }
        break;
    case 6: // OK Case
      controlRelay(0,0,0,0);
      //passTesting(1);
      digitalWrite(passLED, HIGH);
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= decisionDuration){
        sequence = 0;
        lockTime = false;
      }
        break;
    case 7: // NG Case
      controlRelay(0,0,0,0);
      failTesting(1);      
      if(lockTime == false){
        startTime = millis();
        lockTime = true;
      }
      if(millis() - startTime >= decisionDuration){
        sequence = 0;
        lockTime = false;
      }
     break;
   default: // Reset Case

   break;
  }
}

void controlRelay(int A, int B, int C, int D){
  digitalWrite(enableRelayA, A);digitalWrite(enableRelayB, B);
  digitalWrite(enableRelayC, C);digitalWrite(enableRelayD, D);
}

void passTesting(int result){
  digitalWrite(passLED, result);
}

void failTesting(int result){
  digitalWrite(failLED, result);
  digitalWrite(failBuzzer, result);
}
