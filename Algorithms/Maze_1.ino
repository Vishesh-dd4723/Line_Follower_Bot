// Manipulate the rotation of wheels (0-255)

int a=0,b,c,d,e,f,g,re,i,m=0,command;
// Calibrate them according to requirements
int forward_speed = 200;   
int max_turn_speed = 250; 
int min_turn_speed = 50;  
int min_forward_speed = 50; 

void setup() {
  // put your setup code here, to run once:
  pinMode(4,INPUT);         // From sensor 
  pinMode(6,INPUT);         // From sensor
  pinMode(5,INPUT);         // From sensor
  pinMode(3,OUTPUT);        // For motor  left  forward_movement
  pinMode(9,OUTPUT);        // For motor  right forward_movement
  pinMode(10,OUTPUT);       // For motor  left  backward_movement
  pinMode(11,OUTPUT);       // For motor  right backward_movement
}

void loop() {
  // '1' indicates black under it, '0' indicates white.
  // Priority to Right hand movement if both corners indicates high.
  // Sensors order left(4),middle(5),right(6)
  
  b=digitalRead(4);
  c=digitalRead(5);
  d=digitalRead(6);
  command=b*4+c*2+d*1;
  switch (command)
  {
    
    case 0: // Sensors outputs 0,0,0   Moves back
    {
      for(i=1;i<=100;i++)   //moves front
      {
        analogWrite(3,forward_speed);
        analogWrite(9,forward_speed);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        // Checking if get on the path.
        e=digitalRead(4);  
        f=digitalRead(5);
        g=digitalRead(6);
        re=4*e+2*f+7*g;
        if(re == 0){
         delay(5);     // Calibrate it
        }
        else {
          m=1;
          break;
        }
      }
     if(m==0)
     {
      analogWrite(10,forward_speed);
      analogWrite(11,forward_speed);
      digitalWrite(3,LOW);
      digitalWrite(9,LOW);
      delay(1000);
     }
     m=0;
     break;
    }

    case 1: // Sensors outputs 0,0,1   Moves right fast
    {
      analogWrite(3,min_forward_speed);
      analogWrite(11,max_turn_speed);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }

    case 2: // Sensors outputs 0,1,0   Moves straight
    {
      analogWrite(3,forward_speed);
      analogWrite(9,forward_speed);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      delay(10);
      break;
    }

    case 3: // Sensors outputs 0,1,1   Moves right but slowly
    {
      analogWrite(3,min_forward_speed);
      analogWrite(11,min_turn_speed);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      delay(10);
      break;
    }
    
    case 4: // Sensors outputs 1,0,0   Moves left fast
    {
      analogWrite(9,min_forward_speed);
      analogWrite(10,max_turn_speed);
      digitalWrite(11,LOW);
      digitalWrite(3,LOW);
      delay(10);
      break;
    }

    case 5: // Sensors outputs 1,0,1   Moves front
    {
      analogWrite(3,forward_speed);
      analogWrite(9,forward_speed);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      delay(10);
      break;
    }

    case 6: // Sensors outputs 1,1,0   Moves Left but slowly
    {
      analogWrite(10,min_turn_speed);
      analogWrite(9,min_forward_speed);
      digitalWrite(3,LOW);
      digitalWrite(11,LOW);
      delay(10);
      break;
    }
    
    case 7: // Sensors outputs 1,1,1   Moves straight or right
    {
      // Moves front
      
        analogWrite(3,min_forward_speed);
        analogWrite(9,min_forward_speed);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        delay(100);
         
      break;
    }
    default:
    {
      break;
    }
  }
}
