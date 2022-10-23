#define base 0
#define line 1


int CenterSensor=A2;
int LeftCenterSensor=A1;
int LeftFarSensor=A0;
int RightCenterSensor=A3;
int RightFarSensor=A4;

int leftCenterReading;
int CenterReading;
int leftFarReading;
int rightCenterReading;
int rightFarReading;

int replaystage;
float r,l;

#define leapTime 150
int leftMotor1=5;
int leftMotor2=4;
int rightMotor1=6;
int rightMotor2=7;
int enl=3;
int enr=11;
int led=13;
char path[30] = {};
int pathLength;
int readLength;

void setup(){
 pinMode(LeftCenterSensor, INPUT);
 pinMode(CenterSensor, INPUT);
 pinMode(LeftFarSensor, INPUT);
 pinMode(RightCenterSensor, INPUT);
 pinMode(RightFarSensor, INPUT);
 pinMode(leftMotor1, OUTPUT);
 pinMode(leftMotor2, OUTPUT);
 pinMode(rightMotor1, OUTPUT);
 pinMode(rightMotor2, OUTPUT);
 pinMode(enl, OUTPUT);
 pinMode(enr, OUTPUT);
 pinMode(led, OUTPUT);
 digitalWrite(led, HIGH);
 delay(1000);
}

void loop()
{
 readSensors();
 if(leftFarReading==base && rightFarReading==base && (leftCenterReading==line || rightCenterReading==line || CenterReading==line) )
  {straight();}
 else
  {leftHandWall();}
}

void readSensors()
{
 leftCenterReading = digitalRead(LeftCenterSensor);
 CenterReading = digitalRead(CenterSensor);
 leftFarReading = digitalRead(LeftFarSensor);
 rightCenterReading = digitalRead(RightCenterSensor);
 rightFarReading = digitalRead(RightFarSensor);
}

void leftHandWall()
{
  if( leftFarReading==line && rightFarReading==line)
  {
   digitalWrite(leftMotor1, HIGH);
   digitalWrite(leftMotor2, LOW);
   digitalWrite(rightMotor1, HIGH);
   digitalWrite(rightMotor2, LOW);
   analogWrite(enl,180);
   analogWrite(enr,200); 
   delay(leapTime);
   readSensors();
   if((leftFarReading==line && leftCenterReading==line )||( rightFarReading==line && rightCenterReading==line ))
     {done();}
   if(leftFarReading==base && rightFarReading==base)
     {turnLeft();}
  }
  if(leftFarReading==line)
  {
   digitalWrite(leftMotor1, HIGH);
   digitalWrite(leftMotor2, LOW);
   digitalWrite(rightMotor1, HIGH);
   digitalWrite(rightMotor2, LOW);
   analogWrite(enl,180);
   analogWrite(enr,200); 
   delay(leapTime);
   readSensors();
   if(leftFarReading==base && rightFarReading==base)
     {turnLeft();}
   else if((leftFarReading==line && leftCenterReading==line )||( rightFarReading==line && rightCenterReading==line ))                                                    ///////////////// win condition**
     {done();}       
  }
  if(rightFarReading==line)
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200); 
    delay(45);
    readSensors();
    if(leftFarReading==line)
    {
      delay(leapTime-40);
      readSensors();
      if(rightFarReading==line && leftFarReading==line)
      {done();}
      else
      {turnLeft();
       return;
      }
    }
    delay(leapTime-40);
    readSensors();
    if(leftFarReading==base && leftCenterReading==base &&rightCenterReading==base &&  CenterReading==base) 
    {     
      turnRight();
      return;
    }
    path[pathLength]='S';
    pathLength++;
    if(path[pathLength-2]=='B')
    {
      shortPath();
    }
    straight();
  } 
  readSensors();
  if(leftFarReading==base && leftCenterReading==base && rightCenterReading==base&& rightFarReading==base && CenterReading==base)
  {
    turnAround();
  }
}

void done()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
  printPath();
  delay(10000);
  replay();
}

void turnLeft()
{
  while(digitalRead(CenterSensor)==line||digitalRead(RightCenterSensor)==line||digitalRead(LeftCenterSensor)==line)
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,150);
    analogWrite(enr,200); 
    delay(12);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);        
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(6);
  }
  while(digitalRead(CenterSensor)==base)
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,150);
    analogWrite(enr,200); 
    delay(12);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(6);
  }
  if(replaystage==line)
  {
    path[pathLength]='L';
    pathLength++;
    if(path[pathLength-2]=='B')
    {
      shortPath();
    }
  }
}

void turnRight()
{
  while(digitalRead(RightCenterSensor)==line||digitalRead(CenterSensor)==line || digitalRead(LeftCenterSensor)==line)
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(enl,180);
    analogWrite(enr,175); 
    delay(12);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(6);
  }
  while(digitalRead(CenterSensor)==base)
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(enl,180);
    analogWrite(enr,175); 
    delay(12);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(6);
  }
  if(replaystage==line)
  {
    path[pathLength]='R';
    pathLength++;
    if(path[pathLength-2]=='B')
    { shortPath();}
  }
}

void straight()
{
  if(digitalRead(LeftCenterSensor) && !digitalRead(CenterSensor) && !digitalRead(RightCenterSensor))
  {
    digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2,LOW);
    digitalWrite(leftMotor1,LOW);
    digitalWrite(leftMotor2,LOW);
    r=200;
  }
  else if(digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&!digitalRead(RightCenterSensor))
  {
    digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2,LOW);
    digitalWrite(leftMotor1,HIGH);
    digitalWrite(leftMotor2,LOW);
    l=90;
    r=200;
  }
  else if((!digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&!digitalRead(RightCenterSensor))||((digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))))
  {
    l=180;
    r=200;
    digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2,LOW);
    digitalWrite(leftMotor1,HIGH);
    digitalWrite(leftMotor2,LOW);
  }
  else if(!digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))
  {
    digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2,LOW);
    digitalWrite(leftMotor1,HIGH);
    digitalWrite(leftMotor2,LOW);
    l=190;
    r=100;   /////////l and r interchanged
  }
  else if(!digitalRead(LeftCenterSensor) &&!digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))
  {
    digitalWrite(rightMotor1,LOW);
    digitalWrite(rightMotor2,LOW);
    digitalWrite(leftMotor1,HIGH);
    digitalWrite(leftMotor2,LOW);
    l=180;
  }
  analogWrite(enl,l);
  analogWrite(enr,r);
}
 
void turnAround()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(enl,180);
  analogWrite(enr,200); 
  delay(150);
  while(digitalRead(CenterSensor)==base)
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200); 
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW );
    delay(1);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
}

void shortPath()
{
  int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R')
  {
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0)
  {
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0)
  {
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0)
  {
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0)
  {
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0)
  {
    pathLength-=3;
    path[pathLength]='S';
    shortDone=1;
  }
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++; 
}

void printPath()
{
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength)
  {
    Serial.println(path[x]);
    x++;
  }
  Serial.println("+++++++++++++++++");
}

void replay()
{
  readSensors();
  if(leftFarReading==base && rightFarReading==base)
    { straight(); }
  else
  {
   if(path[readLength]=='D')
   {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200); 
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW); 
    endMotion();
   }
   if(path[readLength]=='L')
   {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200);  
    delay(leapTime);
    turnLeft();
   }
   if(path[readLength]=='R')
   {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200); 
    delay(leapTime);
    turnRight();
   }
   if(path[readLength]=='S')
   {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enl,180);
    analogWrite(enr,200); 
    delay(leapTime);
    straight();
   }
   readLength++;
 }
 replay();
}

void endMotion()
{
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(500);
  endMotion();
}
