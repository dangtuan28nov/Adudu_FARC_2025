#pragma once

namespace Lifting{
  //Locations
  constexpr int Up_1 =   13;
  constexpr int Down_1 = 12;
  constexpr int Up_2 =   10;
  constexpr int Down_2 = 11;
  //Specifications
  constexpr int Speed_Lift =      2550;
  constexpr int Speed_Down =      -300;
  constexpr int Speed_Unchanged = 300; //The height of Lift is unchanged
  constexpr int Speed_Climb =     -4050; //Speed of DC motor for climbing

  bool Climb_Status = false;
  unsigned long Time = 0;
  unsigned long Time_Out = 30000; //max climb 30 seconds
  int Prev_Speed = 0;

  //Blueprints for Lifting Motors
  class Scuderia_Lift {
    public:
      void Update(){
        if (ps2x.ButtonPressed(PSB_BLUE)) {
          Climb_Status = !Climb_Status;
          if (Climb_Status) {
            Time = millis();
          }
        }
        if (Climb_Status == true) {
          if (millis() - Time >= Time_Out) {
            Set(0);
            Prev_Speed = 0;
            Climb_Status = false;

          } else {
            Set(Speed_Climb);
            Prev_Speed = Speed_Climb;
          }

        } else if (Climb_Status == false) {
          if (ps2x.Button(PSB_R1)) {
            Set(Speed_Lift);
            Prev_Speed = Speed_Lift;
            
          } else if (ps2x.Button(PSB_R2)) {
            Set(Speed_Down);
            Prev_Speed = Speed_Down;

          } else {
            Set(0);
            Prev_Speed = 0;
          }
        }
      }
    private:
      static void Set(const int Speed){
        if (Speed == 0 || Prev_Speed * Speed == -1 ) {
          //Making sure the motor does not change its direction incontinently
          pwm.setPWM (Up_1, 0, 0);
          pwm.setPWM (Up_2, 0, 0);
          pwm.setPWM (Down_1, 0, 0);
          pwm.setPWM (Down_2, 0, 0);
        } 
        if (Speed > 0){
          pwm.setPWM (Up_1, 0, Speed);
          pwm.setPWM (Up_2, 0, Speed);
        }
        if (Speed < 0){
          pwm.setPWM (Down_1, 0, abs(Speed));
          pwm.setPWM (Down_2, 0, abs(Speed));
        }
      }
  };
}

Lifting::Scuderia_Lift Leclerc; //Leclerc = Name of the Lifters

inline void Lift(){
  Leclerc.Update(); //Leclerc = Name of the Lifters
}