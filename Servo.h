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

  //Blueprints for Servos
  class Scuderia_Servo {
    public:
      void Update(){
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
        static void Set(int Location, int Degree){
        int Servo_Value = map(Degree, 0, 180, 150, 600); //Turn Degree into PWM
        Serial.println (Servo_Value);
        pwm.setPWM (Location, 0, Servo_Value);
      }
  };
}

servo::Scuderia_Servo Schumacher; //Schumacher = Name of the Servos

inline void Servo_Motor(){
  Schumacher.Update(); //Schumacher = Name of the Servos
}