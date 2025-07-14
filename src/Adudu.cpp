#include <Wire.h>
#include <ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib/PS2X_lib.h> //Change to "#include <PS2X_Lib.h>" if you use Arduino.INO

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Include Files
#include <Drivetrain.h>
#include <Lifting.h>
#include <Servo.h>

#define DEBUG
#define PS2_DAT 12  // MISO
#define PS2_CMD 13  // MOSI
#define PS2_SEL 15  // SS
#define PS2_CLK 14  // SLK

// Setup
void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);

  //Connecting to Controller
  Serial.println("Connecting to your Controller");
  int Error = -1;
  for (int i=0; i<10; i ++)
  {
    delay (1000);
    Error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
    if (Error == 0)
    {
      Serial.println("Success");
      break;
    }
    Serial.println("Failed");
  }
  Setup_Drivetrain();
  //SetUp
}

void loop()
{
  ps2x.read_gamepad();
  Servo_Motor();
  Lift();
  Drive();

#ifdef DEBUG
  delay(10);
#endif
}