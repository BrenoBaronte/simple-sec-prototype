// General
int sensorState = LOW;
bool isAlarmActive = false;
int buttonPreviousState = 1;
int buttonCurrentState = 1;

// Leds
const int upLedPin = 2;
const int rightLedPin = 3;
const int downLedPin = 4;

// Sensors
const int upSensorPin = 13;
const int rightSensorPin = 12;
const int downSensorPin = 11;

void setup()
{
  pinMode(upLedPin, INPUT);
  pinMode(upSensorPin, OUTPUT);
  pinMode(rightLedPin, INPUT);
  pinMode(rightSensorPin, OUTPUT);
  pinMode(downLedPin, INPUT);
  pinMode(downSensorPin, OUTPUT);
  
  pinMode(7, OUTPUT);
  
  pinMode(10, INPUT_PULLUP);
    
  Serial.begin(9600);
}

void loop()
{  
  checkSensor(upLedPin, upSensorPin, "Up");
  
  checkSensor(rightLedPin, rightSensorPin, "Right");
  
  checkSensor(downLedPin, downSensorPin, "Down");
  
  checkPiezo();
   
  checkResetButton();
}

void checkSensor(int sensorPin, int ledPin, String direction){
 
  sensorState = digitalRead(sensorPin);
  
  if (sensorState == HIGH) {
    digitalWrite(ledPin, HIGH);
    
    sendAlarmMessage(direction);
    
    isAlarmActive = true;
    
  } 
  else {
    digitalWrite(ledPin, LOW);
  }
}

void sendAlarmMessage(String direction) {
	Serial.print("Sensor ");
    Serial.print(direction);
    Serial.println(" activated");
}

void checkPiezo(){
  if (isAlarmActive == true){
  	playAlarmSound();
  }
}

void playAlarmSound(){
  tone(8, 220, 100);
  delay(250);
}

void checkResetButton(){ 
  
  buttonCurrentState = digitalRead(10);
  
  if (buttonPreviousState == LOW
      && buttonCurrentState == HIGH){
  	resetAlarm();
  }
  
  buttonPreviousState = buttonCurrentState;
}

void resetAlarm(){
  isAlarmActive = false;
  Serial.println("Alarm reseted");
}