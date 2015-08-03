//Pixy arduino robot
//Arduino IDE 1.6.4

#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

int signature = 0;
int x = 0;                      //positon x axis
int y = 0;                      //position y axis
unsigned int width = 0;         //object's width
unsigned int height = 0;        //object's height
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;                  //min x position
int Xmax = 200;                 //max x position
int maxArea = 0;
int minArea = 0;
int motor1 = 4;                 //motor1 on Pin D4
int enable1 = 5;                //enable1 on Pin D5
int motor2 = 7;                 //motor2 on Pin D7
int enable2 = 6;                //enable2 on Pin D6
int Speed = 70;                 //speed for motor
static int i = 0;

void setup()
{ 
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  Serial.begin(9600);
  Stop();
  pixy.init();
}

void loop()
{ 
  while(millis()<5000)
  {
    scan();
    area = width * height; //calculate the object area 
    maxArea = area + 1000;
    minArea = area - 1000;
  }

    scan(); 

  if(signature == 2)//looking for signature 2
  {
    newarea = width * height; //calculate the object area
    
      if (x < Xmin)//turn left if x position < max x position
      {     
       left();
      }
      else if (x > Xmax) //turn right if x position > max x position
      {
       right();
      }
      else if(newarea < minArea)//go forward if object too small
      {
       forward(); 
      }
      else if(newarea > maxArea)//go backward if object too big
      {
       backward(); 
      }
      
      //else stop
      else
      {
        Stop(); 
      } 
   }
   else
   {
    Stop();
     }
}

void backward()//backward
  {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
  }

void forward()//forward
  {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
  }

void right()//turn right
  {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed); 
  }

void left()//turn left
  {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed); 
  }

void Stop()//stop
  {
  digitalWrite(enable1, LOW);
  digitalWrite(enable2, LOW);  
  }
void scan()
  {
  uint16_t blocks;
  blocks = pixy.getBlocks();  //receive data from pixy 
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
  }  
