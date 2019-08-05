#include <IRremote.h>

IRrecv irrecv(12);
decode_results results;

#define POWER 0xE0E040BF
#define BUTTON1 0xE0E020DF
#define BUTTON2 0xE0E0A05F
#define BUTTON3 0xE0E0609F
#define BUTTON4 0xE0E010EF
#define BUTTON5 0xE0E0906F
#define BUTTON6 0xE0E050AF
#define BUTTON7 0xE0E030CF
#define BUTTON8 0xE0E0B04F
#define BUTTON9 0xE0E0708F
#define BUTTON0 0xE0E08877
#define UP 0xE0E006F9
#define LEFT 0xE0E0A659
#define OK 0xE0E016E9
#define RIGHT 0xE0E046B9
#define DOWN 0xE0E08679

const int sen1 = A2;
const int sen2 = A1;
const int sen3 = A0;
const int sen4 = A6;
const int sen5 = A7;
const int rf = 5;
const int rb = 3;
const int lf = 11;
const int lb = 10;
const int ledred = 9;
const int ledgreen = 8;
const int ledblue = 6;
const int buzzer = 4;
const int ledboard = 13;

int tf = 30;
int ff = 80;

int linesenrv;
int linesenlv;
int linesenrst;
int linesenlst;
int thresholdline = 600;

int frontsenv;
int frontsenst;
int thresholdfront = 800;

int leftsenv;
int leftsenst;
int rightsenv;
int rightsenst;
int thresholdsides = 800;

int randNumber;
int countforw = 0;
int countforwthreshold = 8;

int notenum = 8;
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notes[] = {C, D, E, F, G, A, B, C_};

int surfacemode = 1; // 1: smooth , 2: frictioned

void setup() {
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(sen3,INPUT);
  pinMode(sen4,INPUT);
  pinMode(sen5,INPUT);
  pinMode(rf,OUTPUT);
  pinMode(rb,OUTPUT);
  pinMode(lf,OUTPUT);
  pinMode(lb,OUTPUT);
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  pinMode(ledblue,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(ledboard,OUTPUT);
  digitalWrite(ledred,1);
  digitalWrite(ledgreen,1);
  digitalWrite(ledblue,1);
  irrecv.enableIRIn();
  intro();
}

void intro() {
  for (int i = 0; i < notenum; i++) {
    tone(buzzer, notes[i]);
    randNumber = random(0,3);
    if (randNumber == 0) {
      digitalWrite(ledred,0);
      digitalWrite(ledgreen,1);
      digitalWrite(ledblue,1);
    }
    else if (randNumber == 1) {
      digitalWrite(ledred,1);
      digitalWrite(ledgreen,0);
      digitalWrite(ledblue,1);
    }
    else if (randNumber == 2) {
      digitalWrite(ledred,1);
      digitalWrite(ledgreen,1);
      digitalWrite(ledblue,0);
    }
    delay(250);
    noTone(buzzer);
    delay(20);
  }
  noTone(buzzer);
  digitalWrite(ledred,1);
  digitalWrite(ledgreen,1);
  digitalWrite(ledblue,1);
}

void forward() {
  analogWrite(rf,ff);
  analogWrite(lf,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void backward() {
  analogWrite(rb,ff);
  analogWrite(lb,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void leftp() {
  analogWrite(rf,ff);
  analogWrite(lb,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void rightp() {
  analogWrite(rb,ff);
  analogWrite(lf,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void left() {
  analogWrite(rf,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void right() {
  analogWrite(lf,ff);
  delay(tf);
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void stopp() {
  digitalWrite(rf,0);
  digitalWrite(rb,0);
  digitalWrite(lf,0);
  digitalWrite(lb,0);
}

void senread() {
  linesenrv = analogRead(sen3); 
  linesenlv = analogRead(sen2);
  frontsenv = analogRead(sen5);
  leftsenv = analogRead(sen1);
  rightsenv = analogRead(sen4);

  if (linesenrv < thresholdline) {
    linesenrst = 1;
  }
  else {
    linesenrst = 0;
  }
  if (linesenlv < thresholdline) {
    linesenlst = 1;
  }
  else {
    linesenlst = 0;
  }
  if (frontsenv < thresholdfront) {
    frontsenst = 1;
  }
  else {
    frontsenst = 0;
  }
  if (leftsenv < thresholdsides) {
    leftsenst = 1;
  }
  else {
    leftsenst = 0;
  }
  if (rightsenv < thresholdsides) {
    rightsenst = 1;
  }
  else {
    rightsenst = 0;
  }
}

void loop() {
  senread();
  if (irrecv.decode(&results)) {
    if (results.value == BUTTON1) {
      surfacemode = 1; // smooth
    }
    if (results.value == BUTTON2) {
      surfacemode = 2; // fritioned
    }
  }
  if (frontsenst == 1) {
    digitalWrite(ledboard,1);
    digitalWrite(ledred,0);
    digitalWrite(ledgreen,1);
    digitalWrite(ledblue,1);
    digitalWrite(buzzer,1);
    delay(15);
    digitalWrite(buzzer,0);
    countforw = 0;
    if (leftsenst == 1 and rightsenst == 1) {
      tf = 700;
      ff = 80;
      backward();
    }
    else if (leftsenst == 0 and rightsenst == 1) {
      tf = 100;
      ff = 80;
      backward();
      if (surfacemode == 1) {
        tf = 50;
        ff = 200;
      }
      else {
        tf = 200;
        ff = 200;
      }
      leftp();
    }
    else if (leftsenst == 1 and rightsenst == 0) {
      tf = 100;
      ff = 80;
      backward();
      if (surfacemode == 1) {
        tf = 50;
        ff = 200;
      }
      else {
        tf = 200;
        ff = 200;
      }
      rightp();
    }
    else {
      randNumber = random(1,2);
      tf = 30;
      ff = 80;
      backward();
      if (randNumber == 1) {
        if (surfacemode == 1) {
          tf = 50;
          ff = 200;
        }
        else {
          tf = 200;
          ff = 200;
        }
        leftp();
      }
      else {
        if (surfacemode == 1) {
          tf = 50;
          ff = 200;
        }
        else {
          tf = 200;
          ff = 200;
        }
        rightp();
      }
    }
  }
  else {
    digitalWrite(ledboard,0);
    digitalWrite(ledred,1);
    digitalWrite(ledgreen,0);
    digitalWrite(ledblue,1);
    if (linesenlst == 1 and linesenrst == 1) {
      countforw = countforw + 1;
      tf = 30;
      ff = 80;
      forward();
    }
    else if (linesenlst == 0 and linesenrst == 1) {
      tf = 30;
      ff = 80;
      left();
    }
    else if (linesenlst == 1 and linesenrst == 0) {
      tf = 30;
      ff = 80;
      right();
    }
    else {
      if (countforw < countforwthreshold) {
        digitalWrite(ledboard,1);
        digitalWrite(ledred,0);
        digitalWrite(ledgreen,1);
        digitalWrite(ledblue,1);
        stopp();
      }
      else {
        digitalWrite(ledboard,0);
        digitalWrite(ledred,1);
        digitalWrite(ledgreen,1);
        digitalWrite(ledblue,0);
        tf = 60;
        ff = 80;
        backward();
      }
    }
  }
}
