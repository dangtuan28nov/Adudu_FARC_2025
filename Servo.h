#pragma once

namespace servo {
  //Locations
  constexpr int Servo_1 = 2;
  constexpr int Servo_2 = 3;

  //Specifications
  constexpr int Up_1 =   20;
  constexpr int Up_2 =   160;
  constexpr int Down_1 = 160;
  constexpr int Down_2 = 20;

  bool Status_1 = false;
  bool Status_2 = false;
  long Time_1 = 0;
  long Time_2 = 0;
  long Time_Out = 3000; //3 seconds

  //Blueprints for Servos
  class Scuderia_Servo {
    public:
      void Update(){
        const long Present_Time = millis();
        //Checking if Servo whether Servo is running for too long
        if (Status_1 && Present_Time - Time_1 >= Time_Out) {
          Status_1 = false;
          pwm.setPWM (Servo_1,0,0);
        }
        if (Status_2 && Present_Time - Time_2 >= Time_Out) {
          Status_2 = false;
          pwm.setPWM (Servo_2,0,0);
        }

        //Check GamePad
        if (ps2x.Button(PSB_PAD_UP)){
          Set(Servo_1, Up_1); //Set(int Location, int Degree)

        } else if (ps2x.Button(PSB_PAD_DOWN)){
          Set(Servo_1, Down_1);

        } else if (ps2x.Button(PSB_GREEN)){
          Set(Servo_2, Up_2);

        } else if (ps2x.Button(PSB_BLUE)){
          Set(Servo_2, Down_2);
        }
      }
    private:
      void Set(int Location, int Degree){
        int Servo_Value = map(Degree, 0, 180, 150, 600); //Turn Degree into PWM
        pwm.setPWM (Location, 0, Servo_Value);

        if (Location == Servo_1) {
          Status_1 = true;
          Time_1 = millis();

        } else if (Location == Servo_2) {
          Status_2 = true;
          Time_2 = millis();
        }
      }
  };
}

servo::Scuderia_Servo Schumacher; //Schumacher = Name of the Servos

inline void Servo_Motor(){
  Schumacher.Update(); //Schumacher = Name of the Servos
}