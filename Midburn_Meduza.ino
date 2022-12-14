/*
Author: Ido Morel

Probably last version of this code for now since project was presented already
Might make improvements for next year.
TODO:
add limit switch to make sure no manual timing is needed.
*/





#include <YK04_Module.h>
#include <Servo.h>

#define A 2
#define B 5
#define C 7
#define D 6
#define motor 3
#define startB 2
#define pot A2
volatile int val = 0;
volatile bool flag = false;
bool done = false;
volatile bool inter = false;
unsigned long rn;
unsigned long last;

// YK04_Module* module;
Servo worm;

void setup()
{

  // module = new YK04_Module(A, B, C, D);
  worm.attach(motor);
  pinMode(motor, OUTPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  // pinMode(motor, OUTPUT);
  // pinMode(startB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startB), control, RISING);
  pinMode(pot, INPUT);

  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  // analogWrite(motor, 127);
  worm.writeMicroseconds(1500);
  Serial.begin(115200);
  Serial.println("Done");
}

void loop()
{
  // Serial.println("main");

  /*
  if (inter == true){
    while(digitalRead(A) == HIGH){}
    detachInterrupt(digitalPinToInterrupt(startB));
    Serial.println("Waited HERE");
    EIFR = 1;
    inter = false;
  }
  */
  if (flag == false)
  {
    val = map(analogRead(pot), 0, 1023, 800, 2200);
    // Serial.println(val);
    if (val > 1700)
    {
      // digitalWrite(in1, HIGH);
      // digitalWrite(in2, LOW);
      // analogWrite(motor, (val - 20));
      worm.writeMicroseconds(val - 200);
    }
    else if (val < 1300)
    {
      // digitalWrite(in1, LOW);
      // digitalWrite(in2, HIGH);
      //analogWrite(motor, (val * -1) - 20);
      worm.writeMicroseconds(val + 200);
    }
    else
    {
      // Serial.println("Pot disengaged!");
      if (digitalRead(B) == HIGH)
      {
        // analogWrite(motor, 255);
        worm.writeMicroseconds(1800);

        Serial.println("LEFT");
      }
      else if (digitalRead(C) == HIGH)
      {
        // analogWrite(motor, 0);
        worm.writeMicroseconds(1200);

        Serial.println("RIGHT");
      }
      else
      {
        Serial.println("IDLE");
        // analogWrite(motor, 127);
        worm.writeMicroseconds(1500);
      }
    }
  }
  else
  {

    if (done == false)
    {
      last = millis();
      done = true;
    }
    // rn = millis();
    // attachInterrupt(digitalPinToInterrupt(startB), control, RISING);
    Serial.println(digitalRead(startB));
    if (millis() < last + 3000)
    {
      // analogWrite(motor, 210);
      worm.writeMicroseconds(1700);
      Serial.println("Main RIGHT");
    }
    else if (millis() < last + 6250)
    {
      // analogWrite(motor, 100);
      worm.writeMicroseconds(1250);
      Serial.println("Main LEFT");
    }
    else
    {
      done = false;
    }
  }
  // analogWrite(motor, 100);
  // delay(2500);
  // Serial.println("Loop");
}
//  val = map(analogRead(pot), 0, 1023, 0, 510);
//  Serial.println(val);
//  if (val > 255) {
//    digitalWrite(in1, HIGH);
//    digitalWrite(in2, LOW);
//    analogWrite(enA, (val - 255));
//
//  }
//  else {
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, HIGH);
//    analogWrite(enA, val);
//  }
//}

void control()
{
  flag = !flag;
}

/*
void control() {
  detachInterrupt(digitalPinToInterrupt(startB));
  EIFR = 1;
  inter = true;
  while (digitalRead(A) == HIGH) {}
  flag = true;
  Serial.println("interrupt!");
  //while (digitalRead(startB) == HIGH) {
  while (flag == true) {
    val = map(analogRead(pot), 0, 1023, 800, 2200);
    //Serial.println(val);
    if (val > 1700) {
      //digitalWrite(in1, HIGH);
      //digitalWrite(in2, LOW);
      //analogWrite(motor, (val - 20));
      worm.writeMicroseconds(val-200);

    }
    else if (val < 1300) {
      //digitalWrite(in1, LOW);
      //digitalWrite(in2, HIGH);
      analogWrite(motor, (val * -1) - 20);
      worm.writeMicroseconds(val+200);

    }
    else {
      //Serial.println("Pot disengaged!");
      if (digitalRead(B) == HIGH) {
        //analogWrite(motor, 255);
        worm.writeMicroseconds(1800);

        Serial.println("LEFT");
      }
      else if (digitalRead(C) == HIGH) {
        //analogWrite(motor, 0);
        worm.writeMicroseconds(1200);

        Serial.println("RIGHT");
      }
      else {
        Serial.println("IDLE");
        //analogWrite(motor, 127);
      worm.writeMicroseconds(1500);

      }
    }
    delay(50);
    Serial.println("inside");
    while (digitalRead(A) == HIGH) {
      flag = false;
      Serial.println("STUCK HERE");
    }
  }
  detachInterrupt(digitalPinToInterrupt(startB));
  EIFR = 1;
}
*/
