void setup() {
  // put your setup code here, to run once:
  pinMode(5,INPUT);         // For sensor 
  pinMode(7,INPUT);        // For sensor
  pinMode(6,INPUT);         // For sensor
  pinMode(3,OUTPUT);        // For motor
  pinMode(9,OUTPUT);        // For motor
  pinMode(10,OUTPUT);       // For motor
  pinMode(11,OUTPUT);       // For motor
}

void loop() {
  // '0' indicates black under it, '1' indicates white.
  // Prior Right hand movement if both corners indicaies low.
  // Sensors order left(5),middle(6),right(7)
  int a,b,c,d,command;
  b=digitalRead(5);
  c=digitalRead(6);
  d=digitalRead(7);
  command=b*4+c*2+d*1;
  Serial.println(command);
  switch (command)
  {
    case 0: // Sensors outputs 0,0,0   Moves straight or right
    {
      if (a==0)
      {
        analogWrite(3,255);
        analogWrite(9,255);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        delay(10);
        a=1;
      }
      else
      {
        analogWrite(3,255);
        analogWrite(11,128);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        delay(10);
      }
      break;
    }
    case 1: // Sensors outputs 0,0,1   Moves Left but slowly
    {
      analogWrite(10,128);
      analogWrite(9,255);
      digitalWrite(3,LOW);
      digitalWrite(11,LOW);
      delay(10);
      break;
    }
    case 2: // Sensors outputs 0,1,0   Moves right fast
    {
      analogWrite(3,255);
      analogWrite(11,255);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }
    case 3: // Sensors outputs 0,1,1   Moves left fast
    {
      analogWrite(9,255);
      analogWrite(10,255);
      digitalWrite(11,LOW);
      digitalWrite(3,LOW);
      delay(10);
      break;
    }
    case 4: // Sensors outputs 1,0,0   Moves right but slowly
    {
      analogWrite(3,255);
      analogWrite(11,128);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }
    case 5: // Sensors outputs 1,0,1   Moves straight
    {
      analogWrite(3,255);
      analogWrite(9,255);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      delay(10);
      break;
    }
    case 6: // Sensors outputs 1,1,0   Moves right fast
    {
      analogWrite(3,255);
      analogWrite(11,255);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }
    case 7: // Sensors outputs 1,1,1   Moves back
    {
      analogWrite(10,255);
      analogWrite(11,255);
      digitalWrite(3,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }
    default:
    {
      
    }
  }
}
