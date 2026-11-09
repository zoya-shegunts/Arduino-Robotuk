#include <Servo.h>

#define servoPin 10  //The pin of servo

#define ML_Ctrl 4  //Define the direction control pin of the left motor
#define ML_PWM 6   //Define the PWM control pin of the left motor
#define MR_Ctrl 2  //Define the direction control pin of the right motor
#define MR_PWM 5   //Define the PWM control pin of the right motor

#define SCL_Pin  A5  //set a pin of clock to A5
#define SDA_Pin  A4  //set a data pin to A4

#define SPEED_FRONT 120
#define SPEED_BACK 150

int trigPin = 12; // Pin Trig attaches to 12
int echoPin = 13; //Pin Echo attaches to 13
//long duration;
float distance;
bool flag = false;

Servo myservo;
int pos = 0;

int touchPin = 9; //Pin touch attaches to 9
int touchCount = 0;

unsigned char smile[] =
{
    0x00, 0x08, 0x04, 0x02, 0x02, 0x24, 0x48, 0x40, 0x40, 0x48, 0x24, 0x02,
    0x02, 0x04, 0x08, 0x00
};

unsigned char smile1[] =
{
    0x00, 0x08, 0x04, 0x02, 0x02, 0x24, 0x48, 0x40, 0x40, 0x48, 0x24, 0x04,
    0x04, 0x04, 0x08, 0x00
};

unsigned char wink[] =
{
    0x00, 0x08, 0x04, 0x02, 0x02, 0x44, 0x48, 0x40, 0x40, 0x48, 0x28, 0x08,
    0x08, 0x08, 0x08, 0x00
};

unsigned char sad[] =
{
    0x00, 0x00, 0x04, 0x08, 0x10, 0x08, 0x44, 0x20, 0x20, 0x44, 0x08, 0x10,
    0x08, 0x04, 0x00, 0x00
};

unsigned char right[] =
{
    0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xff,
    0xff, 0x7e, 0x3c, 0x18
};

unsigned char left[] =
{
    0x18, 0x3c, 0x7e, 0xff, 0xff, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x3c, 0x3c, 0x3c
};

unsigned char sleepy1[] =
{
    0x00, 0x00, 0x04, 0x08, 0x08, 0x04, 0x60, 0x90, 0x90, 0x60, 0x84, 0x88,
    0x28, 0x64, 0x48, 0x18
};

unsigned char sleepy2[] =
{
    0x00, 0x00, 0x04, 0x08, 0x08, 0x04, 0x60, 0x90, 0x90, 0x60, 0x04, 0x48,
    0xc8, 0x94, 0x30, 0x24
};

unsigned char center[] =
{
    0x00, 0x00, 0x3c, 0x42, 0x5a, 0x42, 0x3c, 0x00, 0x00, 0x3c, 0x42, 0x5a,
    0x42, 0x3c, 0x00, 0x00
};

unsigned char left1[] =
{
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x3c, 0x00, 0x00, 0x3c, 0x42,
    0x5a, 0x5a, 0x3c, 0x00
};
unsigned char left2[] =
{
    0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x5a, 0x3c, 0x00, 0x00, 0x00, 0x3c,
    0x42, 0x5a, 0x3c, 0x00
};

unsigned char right1[] =
{
    0x00, 0x3c, 0x5a, 0x5a, 0x42, 0x3c, 0x00, 0x00, 0x3c, 0x5a, 0x5a, 0x42,
    0x3c, 0x00, 0x00, 0x00
};

unsigned char right2[] =
{
    0x00, 0x3c, 0x5a, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x3c, 0x5a, 0x42, 0x3c,
    0x00, 0x00, 0x00, 0x00
};

unsigned char heart[] =
{
    0x04, 0x0e, 0x1e, 0x3c, 0x1e, 0x0e, 0x44, 0xa0, 0xa0, 0x44, 0x0e, 0x1e,
    0x3c, 0x1e, 0x0e, 0x04
};

unsigned char heart0[] =
{
    0x00, 0x04, 0x0e, 0x1c, 0x0e, 0x04, 0x40, 0xa0, 0xa0, 0x40, 0x04, 0x0e,
    0x1c, 0x0e, 0x04, 0x00
};

void setup() 
{
  pinMode(SCL_Pin, OUTPUT);
  pinMode(SDA_Pin, OUTPUT);

  myservo.attach(servoPin);

//  pinMode(LED, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  myservo.write(110); //Set the angle of the servo to 90°
  delay(500); //delay in 500ms
  
  pinMode(touchPin, INPUT); // set pin for touch

  Serial.begin(9600);
}

void loop() 
{

  if(digitalRead(touchPin) == HIGH){ //check wether the pin is HIGH or LOW
    touchCount++;
    if(touchCount%2){
      for(int i = 0; i < 2; i++)
        animation2(heart0, heart);
    }
    // animation(smile, smile1, wink);
    // animation(wink, smile1, smile);
    Serial.println(touchCount);
  }

  if(touchCount%2){ //if its been touched for odd times then just go
    distance = checkdistance();  //Assign the distance measured by ultrasonic sound to distance
    if(distance <= 20){
      Car_stop();
//      digitalWrite(LED, HIGH);
      matrix_display(sad);
      flag = false;

      //using servo turn the ultrasonic left, then right, get which size has more space, go back 10 cm and go to that side
      int leftDis = lookLeft();
      int rightDis = lookRight();

      myservo.write(110);
      delay(200);

      goBack10cm();

      if(leftDis <= rightDis){
        matrix_display(right);
        Car_right();
        delay(1000);
        Car_stop();
      }
      else{
        matrix_display(left);
        Car_left();
        delay(1000);
        Car_stop();
      }
    }
    else if(!flag){
      Car_stop();
//      digitalWrite(LED, LOW);
      animation(smile, smile1, wink);
      animation(wink, smile1, smile);
      flag = true;
    }
    else{
      Car_front();
      matrix_display(smile);
    }
  }
  else{ //else just wink
    Car_stop();
    animation2(sleepy1, sleepy2);
    animation2(sleepy2, sleepy1);
  }

  delay(50);
}

void Car_front()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, SPEED_FRONT);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, SPEED_FRONT);
}

void Car_back()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, SPEED_BACK);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, SPEED_BACK);
}

void Car_left()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, SPEED_FRONT);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, SPEED_BACK);
}

void Car_right()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, SPEED_BACK);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, SPEED_FRONT);
}

void Car_stop()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
}

void goBack10cm(){
  Car_back();
  delay(500);
  Car_stop();
}

float checkdistance() 
{
  static float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH) / 58.20;  //The 58.20 here comes from 2*29.1=58.2
  delay(10);
  return distance;
}

//this function is used for the display of dot matrix 
void matrix_display(unsigned char matrix_value[])
{
  IIC_start();  //use the function to start transmitting data
  IIC_send(0xc0);  //select an address

  for (int i = 0; i < 16; i++) //image data have 16 characters
  {
    IIC_send(matrix_value[i]); //data to transmit pictures
  }

  IIC_end();   //end the data transmission of pictures

  IIC_start();
  IIC_send(0x8A);  //show control and select pulse width 4/16
  IIC_end();
}

//the condition that data starts transmitting
void IIC_start()
{
  digitalWrite(SDA_Pin, HIGH);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, LOW);
}

//the sign that transmission of data ends
void IIC_end()
{
  digitalWrite(SCL_Pin, LOW);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, HIGH);
  delayMicroseconds(3);
}

//transmit data
void IIC_send(unsigned char send_data)
{
  for (byte mask = 0x01; mask != 0; mask <<= 1) //each character has 8 digits, which is detected one by one
  {
    if (send_data & mask) { //set high or low levels in light of each bit(0 or 1)
      digitalWrite(SDA_Pin, HIGH);
    } else {
      digitalWrite(SDA_Pin, LOW);
    }
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH); //pull up the clock pin SCL_Pin to end the transmission of data
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, LOW); //pull down the clock pin SCL_Pin to change signals of SDA
  }
}

void animation(unsigned char data1[], unsigned char data2[], unsigned char data3[])
{
  matrix_display(data1);
  delay(100);
  matrix_display(data2);
  delay(100);
  matrix_display(data3);
  delay(100);
}

void animation2(unsigned char data1[], unsigned char data2[])
{
  matrix_display(data1);
  delay(500);
  matrix_display(data2);
  delay(500);
}

float lookLeft(){
  animation(center, left1, left2);
  myservo.write(175);
  delay(1000);
  animation(left2, left1, center);
  return checkdistance();
}

float lookRight(){
  animation(center, right1, right2);
  myservo.write(30);
  delay(1000);
  animation(right2, right1, center);
  return checkdistance();
}