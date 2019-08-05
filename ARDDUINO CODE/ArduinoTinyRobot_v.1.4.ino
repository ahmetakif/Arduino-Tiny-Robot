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

int surfacemode; // 1: smooth , 2: frictioned
int accelmode;
float acceldelay = 0.5;

int introlen = 1;

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
  intro();
  modeselection();
}

void intro() {
  for (int i = 0; i < introlen; i++) {
    digitalWrite(buzzer,1);
    digitalWrite(ledred,0);
    digitalWrite(ledgreen,1);
    digitalWrite(ledblue,1);
    delay(50);
    digitalWrite(buzzer,0);
    delay(200);
    digitalWrite(buzzer,1);
    digitalWrite(ledred,1);
    digitalWrite(ledgreen,0);
    digitalWrite(ledblue,1);
    delay(50);
    digitalWrite(buzzer,0);
    delay(200);
    digitalWrite(buzzer,1);
    digitalWrite(ledred,1);
    digitalWrite(ledgreen,1);
    digitalWrite(ledblue,0);
    delay(50);
    digitalWrite(buzzer,0);
    delay(200);
  }
  analogWrite(buzzer,0);
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

void accelforward() {
  for (int x = 0; x < ff; x++) {
    analogWrite(rf,x);
    analogWrite(lf,x);
    analogWrite(rb,0);
    analogWrite(lb,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
}

void accelbackward() {
  for (int x = 0; x < ff; x++) {
    analogWrite(rb,x);
    analogWrite(lb,x);
    analogWrite(rf,0);
    analogWrite(lf,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
}

void accelleft() {
  for (int x = 0; x < ff; x++) {
    analogWrite(rf,x);
    analogWrite(lf,0);
    analogWrite(rb,0);
    analogWrite(lb,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
}

void accelright() {
  for (int x = 0; x < ff; x++) {
    analogWrite(lf,x);
    analogWrite(rf,0);
    analogWrite(rb,0);
    analogWrite(lb,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
}

void accelleftp() {
  for (int x = 0; x < ff; x++) {
    analogWrite(rf,x);
    analogWrite(lb,x);
    analogWrite(rb,0);
    analogWrite(lf,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
}

void accelrightp() {
  for (int x = 0; x < ff; x++) {
    analogWrite(rb,x);
    analogWrite(lf,x);
    analogWrite(rf,0);
    analogWrite(lb,0);
    delay(acceldelay);
  }
  analogWrite(rf,0);
  analogWrite(lf,0);
  analogWrite(rb,0);
  analogWrite(lb,0);
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

void modeselection() {
  senread();
  if (leftsenst == 1) { 
    digitalWrite(ledblue,0);
    delay(200);
    digitalWrite(ledblue,1);
    delay(500);
    digitalWrite(ledblue,0);
    delay(200);
    digitalWrite(ledblue,1);
    delay(500);
    surfacemode = 1;
  }
  else if (rightsenst == 1) {
    digitalWrite(ledred,0);
    delay(200);
    digitalWrite(ledred,1);
    delay(500);
    digitalWrite(ledred,0);
    delay(200);
    digitalWrite(ledred,1);
    delay(500);
    surfacemode = 2;
  }
  if (frontsenst == 1) {
    digitalWrite(ledred,0);
    digitalWrite(ledblue,0);
    delay(200);
    digitalWrite(ledred,1);
    digitalWrite(ledblue,1);
    delay(500);
    digitalWrite(ledred,0);
    digitalWrite(ledblue,0);
    delay(200);
    digitalWrite(ledred,1);
    digitalWrite(ledblue,1);
    delay(500);
    accelmode = 1;
  }
  else {
    accelmode = 0;
  }
}

void loop() {
  senread();
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
      if (accelmode == 1) {
        accelbackward();
      }
      tf = 700;
      ff = 80;
      backward();
    }
    else if (leftsenst == 0 and rightsenst == 1) {
      if (accelmode == 1) {
        accelbackward();
      }
      tf = 100;
      ff = 80;
      backward();
      if (surfacemode == 1) {
        tf = 50;
        ff = 200;
      }
      else if (surfacemode == 2) {
        tf = 200;
        ff = 200;
      }
      if (accelmode == 1) {
        accelleftp();
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
      else if (surfacemode == 2) {
        tf = 200;
        ff = 200;
      }
      if (accelmode == 1) {
        accelrightp();
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
        else if (surfacemode == 2) {
          tf = 200;
          ff = 200;
        }
        if (accelmode == 1) {
          accelleftp();
        }
        leftp();
      }
      else {
        if (surfacemode == 1) {
          tf = 50;
          ff = 200;
        }
        else if (surfacemode == 2) {
          tf = 200;
          ff = 200;
        }
        if (accelmode == 1) {
          accelrightp();
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
      if (accelmode == 1) {
        accelforward();
      }
      tf = 30;
      ff = 80;
      forward();
    }
    else if (linesenlst == 0 and linesenrst == 1) {
      if (accelmode == 1) {
        accelleft();
      }
      tf = 30;
      ff = 80;
      left();
    }
    else if (linesenlst == 1 and linesenrst == 0) {
      if (accelmode == 1) {
        accelright();
      }
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
        if (accelmode == 1) {
          accelbackward();
        }
        tf = 60;
        ff = 80;
        backward();
      }
    }
  }
}
