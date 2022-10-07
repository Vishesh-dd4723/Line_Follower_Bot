#define m1 10  //Right Motor MA1
#define m2 9 //Right Motor MA2
#define m3 5  //Left Motor MB1
#define m4 6  //Left Motor MB2

#define s4 4
#define s1 8
#define s2 7
#define s3 12
#define s5 13
void setup ()
{
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}
  void Forward()
  {
    analogWrite(m4,255);
    analogWrite(m1,0);
    analogWrite(m2,255);
    analogWrite(m3,0);


  }
void Right()
{
analogWrite(m1,0);
analogWrite(m2,0);
analogWrite(m3,255);
analogWrite(m4,0);
}

void Left()
{
analogWrite(m1,0);
analogWrite(m4,255);
analogWrite(m2,0);
analogWrite(m3,0);

}
void Back()
{
analogWrite(m1,255);
analogWrite(m4,0);
analogWrite(m3,255);
analogWrite(m2,0);


}
void Stop()
{
analogWrite(m1,0);
analogWrite(m4,0);
analogWrite(m3,0);
analogWrite(m2,0);


}



void loop ()
{
int   IR1 = digitalRead(s1);
int   IR2 = digitalRead(s2);
 int  IR3 = digitalRead(s3);

  if (IR1 == LOW && IR2 == HIGH && IR3 == LOW)//Straight path
    {
     Forward();
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == LOW)//Left turn
    {
     Right();
     delay(500);
    }

  if (IR1 == LOW && IR2 == LOW && IR3 == HIGH)//Right Turn
    {
      Left();
      delay(500);
    }

//  if (IR1 == HIGH && IR2 == LOW && IR3 == HIGH)//T Intersection
//    {
//      Right(); // As left is possible
//    }

//  if (IR1 == HIGH && IR2 == HIGH && IR3 == LOW)//Left T Intersection
//    {
//      Right();// As Left is possible
//    }

//  if (IR1 == LOW && IR2 == HIGH && IR3 == HIGH)//Right T Tntersection
//    {
//     Left();//As Straight path is possible
//    }

//  if (IR1 == LOW && IR2 ==LOW && IR3 == LOW)//Dead End
//    {
//      Stop(); //As no other direction is possible
//    }

//  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//4 Lane intersection
//    {
//     Right(); //As no other direction is possible
//    }

//  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//End of Maze
//    {
////     Stop(); //As no other direction is possible
//    }
}