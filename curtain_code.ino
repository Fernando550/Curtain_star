#include <IRremote.h> 

IRrecv IR(3);
// Motor Connections (Both must use PWM pins)
#define IN1 9
#define IN2 10
#define UpButton 2
#define DownButton 3

const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

unsigned long lastTimeButtonChanged = millis();
const unsigned long debounceDuration = 300;

void setup() {
// Set infrared 
  IR.enableIRIn();

// Set terminal
  Serial.begin(9600);

// Set motor connections as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

// Set button up and down
  pinMode(UpButton, INPUT_PULLUP);
  pinMode(DownButton, INPUT_PULLUP);

  // Stop motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
 
void loop() {
  unsigned long currentTime = millis();

  //Set button to move up
  if (currentTime - lastTimeButtonChanged >= debounceDuration){
      if (digitalRead(UpButton) != HIGH){
        lastTimeButtonChanged = currentTime;
        Serial.println("Button prest up");
        MoveUpCurtain();
    }
  }

  //Set button to move down
  if (currentTime - lastTimeButtonChanged >= debounceDuration){
    if (digitalRead(DownButton) != HIGH){
      lastTimeButtonChanged = currentTime;
      Serial.println("Button prest Down");
      MoveDownCurtain();
    }
  }


//Infrared sensor signal
  if (IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    delay(1500);
    IR.resume();
  }
 
}


//Funtions

void MoveUpCurtain(){
  // Accelerate forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
}

void MoveDownCurtain(){
  // Accelerate Down
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}