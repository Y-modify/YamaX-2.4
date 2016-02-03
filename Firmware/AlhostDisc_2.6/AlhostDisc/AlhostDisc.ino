/*************************************
* AlhostDiscrete v2.5
* Altra モーター系統コマンド制御システム for YamaX 2.4
* made by Y-modify, Nyanyan & coord.e
* Copyright © 2015 Y-modify All Rights Reserved.
*************************************/

/*****Headers*****/
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SerialCommand.h>

/*****Servo Driver I2C Address Setting*****/
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//1
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);//2

/*****Pulse Adjust*****/
#define SERVOMIN  150 //on 0°,0~4095
#define SERVOMAX  600 //on 180°,0~4095

/*****Servo Ports Definition*****/
#define servoA 15

#define servoB 14
#define servoC 13
#define servoD 12

#define servoE 16
#define servoF 17
#define servoG 18

#define servoH 19
#define servoI 21

#define servoK 24
#define servoL 25
#define servoM 26
#define servoN 27
#define servoO 28

#define servoQ 7
#define servoR 6
#define servoS 5
#define servoT 4
#define servoU 3

/*****LED Ports Definition*****/
#define LEDr 11
#define LEDb 10
#define LEDg 9

/*****Object Making*****/
SerialCommand SCmd;

/*****System Setup*****/
void setup()
{
  //Serial Control Begin
  Serial.begin(9600);
  Serial.println("HELLO YamaX 2.4");
  //Serial Command Control Initialize
  SCmd.addCommand("w", walkStep);
  SCmd.addCommand("r", tRightStep);
  SCmd.addCommand("l", tLeftStep);
  SCmd.addCommand("b", bowS);
  SCmd.addCommand("s", stand);
  SCmd.addCommand("n", noS);
  SCmd.addCommand("lr", ledRedAdj);
  SCmd.addCommand("lg", ledGreenAdj);
  SCmd.addCommand("lb", ledBlueAdj);
  SCmd.addDefaultHandler(what);

  //Servo Driver Setup
  pwm1.begin();
  pwm2.begin();
  pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //Start
  blue();
  stand();
  delay(1000);
  green();
}

/*****Command Waiting Loop*****/
void loop() {
  SCmd.readSerial();  //Just it
}

/*****Functions for Response*****/
void walkStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      walk(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void bowS(){
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer  
    bow();
    delay(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void noS(){  
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer  
    no(val);
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void tRightStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      turnright(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void tLeftStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int steps = atoi(arg);    // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL)
    {
      int del = atol(arg);
      turnleft(steps, del);
    }
    else {
      what();
    }
  }
  else {
    what();
  }
  stand();
  clearBuf();
}

void ledRedAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    pwm1.setPWM(LEDg, 0, val);//赤
  }
  else {
    what();
  }
  clearBuf();
}
void ledGreenAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    pwm1.setPWM(LEDr, 0, val);//赤
  }
  else {
    what();
  }
  clearBuf();
}

void ledBlueAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    int val = atoi(arg);    // Converts a char string to an integer
    pwm1.setPWM(LEDb, 0, val);//赤
  }
  else {
    what();
  }
  clearBuf();
}

void what(){
  no(2);
}

void clearBuf(){
  while(Serial.available())
    Serial.read();
}

/*****Base Functions*****/
void stand()
{
  setServoPulse(servoA, 90); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 65);
  setServoPulse(servoI, 70); //腰

  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足

}



void bow()
{
  setServoPulse(servoA, 90); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 65);
  setServoPulse(servoI, 130); //腰


  setServoPulse(servoK, 140);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 140);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足


  setServoPulse(servoQ, 10);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 40);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 90); //左足

}

void foot(int times, int delaytime)
{
  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    delay(delaytime);
    foot2();
    delay(delaytime);
  }
}

void foot1()//左足上げ
{
  setServoPulse(servoA, 90); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 60);
  setServoPulse(servoI, 74); //腰


  setServoPulse(servoK, 120);//-10
  setServoPulse(servoL, 20);//-25
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 40); //右足 -25


  setServoPulse(servoQ, 10);//-10
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 15);//-10
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 45); //左足 -35

  /*  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足*/
}

void foot2()//右足上げ
{
  setServoPulse(servoA, 90); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 70);
  setServoPulse(servoI, 74); //腰


  setServoPulse(servoK, 140);//+10
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 155);//+10
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 100); //右足 +35


  setServoPulse(servoQ, 10);//-10
  setServoPulse(servoR, 170);//+25
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 115); //左足 +35

  /*  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足*/
}



/**********************前進**********************/
void walk(int times, int delaytime)
{
  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    delay(delaytime);
    walk1();
    delay(delaytime);

    foot2();
    delay(delaytime);
    walk2();
    delay(delaytime);
  }
}

void walk1()//左足を出す
{

  setServoPulse(servoA, 30); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 50);
  setServoPulse(servoI, 74); //腰

  //0,10,20,0,0,35
  setServoPulse(servoK, 150);//+20
  setServoPulse(servoL, 35);//-10
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 55); //右足 -10

  //0
  setServoPulse(servoQ, 52);//+32
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 55);//+30
  setServoPulse(servoT, 40);//-20
  setServoPulse(servoU, 75); //左足 -5 

  /*  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足*/


}



void walk2()//右足を出す
{

  setServoPulse(servoA, 150); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 80);
  setServoPulse(servoI, 74); //腰

  setServoPulse(servoK, 98);//-32
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 115);//-30
  setServoPulse(servoN, 90);//+20
  setServoPulse(servoO, 70); //右足 +5

  //0,10,20,0,0,35
  setServoPulse(servoQ, 0);//-20
  setServoPulse(servoR, 155);//+10
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 110); //左足 +30

  /*  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足*/
}
/************************************************/



/**********************回ろう**********************/
void turnright(int times, int delaytime)
{
  for (int i = 0; i < times; i ++)
  {
    foot1();
    delay(delaytime);
    walk1();
    delay(delaytime);
    stand();
    delay(delaytime);
  }

}

void turnleft(int times, int delaytime)
{
  for (int i = 0; i < times; i ++)
  {
    foot2();
    delay(delaytime);
    walk2();
    delay(delaytime);
    stand();
    delay(delaytime);
  }
}
/**************************************************/




/***首***/

void no(int times)
{
  for (int i = 0; i < times; i ++)
  {
    no1();
    delay(200);
    no2();
    delay(200);
  }
}

void no1()
{
  setServoPulse(servoA, 30); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 65);
  setServoPulse(servoI, 65); //腰

  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足
}

void no2()
{
  setServoPulse(servoA, 150); //首

  setServoPulse(servoB, 80);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 70); //左腕

  setServoPulse(servoE, 70);
  setServoPulse(servoF, 180);
  setServoPulse(servoG, 80); //右腕

  setServoPulse(servoH, 65);
  setServoPulse(servoI, 65); //腰

  setServoPulse(servoK, 130);
  setServoPulse(servoL, 45);
  setServoPulse(servoM, 145);
  setServoPulse(servoN, 70);
  setServoPulse(servoO, 65); //右足

  setServoPulse(servoQ, 20);
  setServoPulse(servoR, 145);
  setServoPulse(servoS, 25);
  setServoPulse(servoT, 60);
  setServoPulse(servoU, 80); //左足
}

/********/


/***目のLED***/
void white()
{
  pwm1.setPWM(LEDr, 0, 4095);//赤
  pwm1.setPWM(LEDb, 0, 2300);//青
  pwm1.setPWM(LEDg, 0, 2400);//緑

}

void red()
{
  pwm1.setPWM(LEDr, 0, 4095);//赤
  pwm1.setPWM(LEDb, 0, 0);//青
  pwm1.setPWM(LEDg, 0, 0);//緑

}

void green()
{
  pwm1.setPWM(LEDr, 0, 0);//赤
  pwm1.setPWM(LEDb, 0, 0);//青
  pwm1.setPWM(LEDg, 0, 2400);//緑

}

void blue()
{
  pwm1.setPWM(LEDr, 0, 0);//赤
  pwm1.setPWM(LEDb, 0, 2300);//青
  pwm1.setPWM(LEDg, 0, 0);//緑

}

void purple()
{
  pwm1.setPWM(LEDr, 0, 4095);//赤
  pwm1.setPWM(LEDb, 0, 2300);//青
  pwm1.setPWM(LEDg, 0, 0);//緑

}

void emerald()
{
  pwm1.setPWM(LEDr, 0, 0);//赤
  pwm1.setPWM(LEDb, 0, 2300);//青
  pwm1.setPWM(LEDg, 0, 4095);//緑

}

void yellow()
{
  pwm1.setPWM(LEDr, 0, 4095);//赤
  pwm1.setPWM(LEDb, 0, 0);//青
  pwm1.setPWM(LEDg, 0, 2095);//緑

}
/*****Core Functions*****/
uint8_t setServoPulse(uint8_t n, uint8_t degress) {
  if (degress > 180)
    return false;
  double pulse = map(degress, 0, 180, SERVOMIN, SERVOMAX);
  //Serial.println(pulse);
  if (n < 16) {
    pwm1.setPWM(n, 0, pulse);
  }
  else if (n < 32) {
    pwm2.setPWM(n - 16, 0, pulse);
  }
  else {
    return false;
  }
  return pulse;
}

/*****That's all. Enjoy!*****/
