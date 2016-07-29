int led1 = 3;
int led2 = 5;
int led3 = 6;
int irSensor = A0;
int sensorValue = 0;
int relayRed = 8;
int relayWhite = 9;
int motor11 = 1; //enable pin
int motor12 = 2; //A
int motor13 = 4; //B
int motor21 = 10; //enable pin
int motor22 = 11; //A
int motor23 = 12; //B
int counter = 0; 
boolean isMotor1Running = false;
boolean isMotor2Running = false;
boolean isRelayRedOn = false;
boolean isRelayWhiteOn = false;
boolean isMotorUpLast1 = false;
boolean isMotorUpLast2 = false;
boolean wokeUp = false; 
boolean neckMoved = false;
unsigned long motorTimer1 = 0;
unsigned long motorTimer2 = 0;
unsigned long relayTime = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(irSensor, INPUT);
  pinMode(motor11, OUTPUT);
  pinMode(motor12, OUTPUT);
  pinMode(motor13, OUTPUT);
  pinMode(motor21, OUTPUT);
  pinMode(motor22, OUTPUT);
  pinMode(motor23, OUTPUT);
  digitalWrite(motor11, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor12, LOW);
  digitalWrite(motor22, LOW);
  Serial.begin(9600);
  Serial.print("Hello World");
}

void loop() {
  counter++;

  int irValue = analogRead(irSensor);
  if(irValue <= 400 && irValue > 800) {
    setColor(0, 0, 0);
   //Nothing sensed 
   if (counter > 10000) {
    //this is the "I've been asleep for a while, let's reset" code
    wokeUp = false; 
    neckMoved = false; 
    counter = 0;
   }
   }
   
  if(irValue > 512 && irValue <= 800) {
    setColor(irValue*random(0,255), 0,irValue*random(0,255) );
   //something sensed
  wokeUp = true; 
  }
  Serial.println(irValue);
  if (irValue > 512 && irValue < 800) { runBothMotors(); stopBothMotors(); delay(1500); downBothMotors(); stopBothMotors(); }

if (wokeUp&& !neckMoved) { 
   runBothMotors(); 
   stopBothMotors(); delay(1500);
   downBothMotors(); stopBothMotors(); counter = 0; neckMoved = true;}

}
void runBothMotors() {
  analogWrite(motor11,255);
  analogWrite(motor12,255);
  analogWrite(motor21,255);
  analogWrite(motor22,255);  
  delay(500);
  }

  void downBothMotors() {
  analogWrite(motor11,-255);
  analogWrite(motor12,-255);
  analogWrite(motor21,-255);
  analogWrite(motor22,-255);
  delay(500); 
  }

void stopBothMotors() {
   digitalWrite(motor11, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor12, LOW);
  digitalWrite(motor22, LOW);
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(led1, red);
  analogWrite(led2, green);
  analogWrite(led3, blue);  
}


void motorOne() {
  if(!isMotorUpLast1) {
    digitalWrite(motor12, HIGH);
    digitalWrite(motor13, HIGH);
    digitalWrite(motor12, HIGH);
    digitalWrite(motor11, HIGH);
    isMotor1Running = true;
    isMotorUpLast1 = !isMotorUpLast1;
    motorTimer1 = millis();
  }
  else if(isMotorUpLast1) {
    digitalWrite(motor12, LOW);
    digitalWrite(motor13, LOW);
    digitalWrite(motor13, HIGH);
    digitalWrite(motor11, HIGH);
    isMotor1Running = true;
    isMotorUpLast1 = !isMotorUpLast1;
    motorTimer1 = millis();
  }
}

void motorTwo() {
  if(!isMotorUpLast2) {
    digitalWrite(motor22, LOW);
    digitalWrite(motor23, LOW);
    digitalWrite(motor22, HIGH);
    digitalWrite(motor21, HIGH);
    isMotor2Running = true;
    isMotorUpLast2 = !isMotorUpLast2;
    motorTimer2 = millis();
  }
  else if(isMotorUpLast2) {
    digitalWrite(motor22, LOW);
    digitalWrite(motor23, LOW);
    digitalWrite(motor23, HIGH);
    digitalWrite(motor21, HIGH);
    isMotor2Running = true;
    isMotorUpLast2 = !isMotorUpLast2;
    motorTimer2 = millis();
  }
}

void relayFire() {
  if(isRelayRedOn) {
    digitalWrite(relayRed, LOW);
    digitalWrite(relayWhite, HIGH);
    isRelayRedOn = false;
    isRelayWhiteOn = true;
  }
  else if(isRelayWhiteOn) {
    digitalWrite(relayWhite, LOW);
    digitalWrite(relayRed, HIGH);
    isRelayWhiteOn = false;
    isRelayRedOn = true;
  }  
}

void irLogic() {
  
}



