/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
void redOff();
void redOn();
void greenOff();
void greenOn();
void redFlip();
void greenFlip();
void flipRedGreen();

int greenLight = 7;
int redLight = 8;
int greenDelay;
int redDelay;
int randDelay;
int delayTime;
// Case 4:
int turn;
int case4_delayTime = 500;
int turnDelay;
int prevHigh = 0;

int plan;
bool greenState;
bool redState;

unsigned long currentTime;
unsigned long lastGreenTime;
unsigned long lastRedTime;
unsigned long lastRandTime;
unsigned long lastTurnTime;
unsigned long lastGreenPushed;

int buttonPin = 12;
int buttonPushed = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(buttonPin, INPUT);
   
  Serial.begin(9600);
  // initialize digital pins as an outputs.
  pinMode(greenLight, OUTPUT);
  pinMode(redLight, OUTPUT);

  delayTime = 200;//random(15,750);
  redDelay = random(15,1000);
  greenDelay = random(15,1000);
  randDelay = random(500,5000);
  turnDelay = 5000;
  plan = 3;
  turn = 0;
  greenState = 0;
  redState = 0;
  lastTurnTime = millis();
}

// the loop function runs over and over again forever
void loop() {
  //int redDelay;
  //int greenDelay;
  /*redDelay = random(1,1000);
  greenDelay = random(10,1000);
  delayDiff
  
  delayTime = random(15,750);
  digitalWrite(greenLight, HIGH);
  digitalWrite(redLight, HIGH);
  
  delay(delayTime);
  digitalWrite(greenLight, LOW);
  digitalWrite(redLight, LOW);
  delay(delayTime);
*/
  //currentTime = millis();
  //if (currentTime - lastGreenPushed > 7000)

  //buttonPushed = digitalRead(buttonPin);
  buttonPushed = HIGH;
  if (buttonPushed==LOW)
  {
      prevHigh = 0;
  }
  if (buttonPushed==HIGH && prevHigh==0)
  {
    //lastGreenPushed = currentTime;
    //buttonPushed = digitalRead(buttonPin);
    Serial.print("push: ");
    Serial.println(buttonPushed);
    if (buttonPushed)
    {
        plan++;
        if (plan > 5)
          plan = 1;
    }
    buttonPushed = LOW;
    prevHigh = 1;
  }
  Serial.print("plan: ");
  Serial.println(plan);  

  // 17.12.15 - just for party without button - awesome
  plan = 3;
  
  switch (plan){
    case 1:
      // green red green red ...
      digitalWrite(greenLight, HIGH);
      digitalWrite(redLight, LOW);
      delay(delayTime);
      digitalWrite(redLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(delayTime);
      break;
    
    case 2:
      // steady flicker:
      // green flickers at rate 1
      // red   flickers at rate 2
      currentTime = millis();
      if (currentTime - lastGreenTime > greenDelay){
        lastGreenTime = currentTime;
        greenFlip();
      }
      if (currentTime - lastRedTime > redDelay){
        lastRedTime = currentTime;
        redFlip();
      }
      break;
    
    case 3:
      // changing seperated green & red flickers
      currentTime = millis();
      if (currentTime - lastGreenTime > greenDelay){
        lastGreenTime = currentTime;
        greenFlip();
      }
      if (currentTime - lastRedTime > redDelay){
        lastRedTime = currentTime;
        redFlip();
      }
      if (currentTime - lastRandTime > randDelay){
        lastRandTime = currentTime;
        randomRed();
        randomGreen();
      }
      
      break;
    
    case 4:
      // 1. red   slow to fast
      // 2. green slow to fast
      Serial.print("case4_delayTime = ");
      Serial.println(case4_delayTime);
      case4_delayTime -= 2;
      if (case4_delayTime <= 0){
        case4_delayTime = 500;
        turn = 1 - turn;
        if (redState)
          redFlip();
        if (greenState)
          greenFlip();
        
      }

      currentTime = millis();
      if ((turn == 0) && (currentTime - lastGreenTime > case4_delayTime)){
        lastGreenTime = currentTime;
        greenFlip();
      }
      
      if ((turn == 1) && (currentTime - lastRedTime > case4_delayTime)){
        lastRedTime = currentTime;
        redFlip();
      }
      break;
      
    case 5:
      // green red green red ... slow to fast
      Serial.print("case4_delayTime = ");
      Serial.println(case4_delayTime);
      case4_delayTime -= 2;
      if (case4_delayTime <= 0){
        case4_delayTime = 500;
      }

      currentTime = millis();
      if (currentTime - lastGreenTime > case4_delayTime){
        lastGreenTime = currentTime;
        flipRedGreen();
      }
      break;
    case 6:
      break;
    case 7:
      break;
  }
}


// ------------- Aux Functions -------------
void redOff(){
  redState = 0;
  digitalWrite(redLight, LOW);
}
void redOn(){
  redState = 1;
  digitalWrite(redLight, HIGH);
}
void greenOff(){
  greenState = 0;
  digitalWrite(greenLight, LOW);
}
void greenOn(){
  greenState = 1;
  digitalWrite(greenLight, HIGH);
}

void redFlip(){
  Serial.println("redFlip");
  redState = 1-redState;
  digitalWrite(redLight, redState);
}

void greenFlip(){
  Serial.println("greenFlip");
  greenState = 1-greenState;
  digitalWrite(greenLight, greenState);
}

void flipRedGreen(){
  Serial.println("flipRedGreen");
  Serial.println(redState);
  if (redState == 1){
    redOff();
    greenOn();
  }
  else{
    redOn();
    greenOff();
  }
}

void randomRed(){
  redDelay = random(15,1000);
}

void randomGreen(){
  greenDelay = random(15,1000);
}
