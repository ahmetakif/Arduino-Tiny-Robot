const int sen1 = A2;
const int sen2 = A1;
const int sen3 = A0;
const int sen4 = A6;
const int sen5 = A7;
const int rf = 5;
const int rb = 3;
const int lf = 11;
const int lb = 10;

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
  pinMode(13,OUTPUT);
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

  if (frontsenst == 1) {
    digitalWrite(13,1);
    countforw = 0;
    if (leftsenst == 1 and rightsenst == 1) {
      tf = 700;
      backward();
    }
    else if (leftsenst == 0 and rightsenst == 1) {
      tf = 100;
      backward();
      tf = 700;
      leftp();
    }
    else if (leftsenst == 1 and rightsenst == 0) {
      tf = 100;
      backward();
      tf = 700;
      rightp();
    }
    else {
      randNumber = random(1,2);
      tf = 30;
      backward();
      if (randNumber == 1) {
        tf = 700;
        leftp();
      }
      else {
        tf = 700;
        rightp();
      }
    }
  }
  else {
    digitalWrite(13,0);
    if (linesenlst == 1 and linesenrst == 1) {
      countforw = countforw + 1;
      tf = 30;
      forward();
    }
    else if (linesenlst == 0 and linesenrst == 1) {
      tf = 30;
      left();
    }
    else if (linesenlst == 1 and linesenrst == 0) {
      tf = 30;
      right();
    }
    else {
      if (countforw < countforwthreshold) {
        stopp();
      }
      else {
        tf = 60;
        backward();
      }
    }
  }
}
