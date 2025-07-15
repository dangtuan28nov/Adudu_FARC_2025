#pragma once

namespace Drivetrain {
  //Locations
  constexpr int Left_Up =    8;
  constexpr int Left_Down =  9;
  constexpr int Right_Up =   14;
  constexpr int Right_Down = 15;
  
  //Specifications
  constexpr int Max_Verstappen =    2300; //Max Speed
  constexpr int Charles_Leclerc =   1750; //Normal Speed
  constexpr int Pit_Zone =          30; //The area very close to Origin
  constexpr int Origin =            127;
  constexpr float Smooth_Operator = 0.3; //Use to smooth the change in speed

  int Left_Speed =  0;
  int Right_Speed = 0;
  int Prev_Right =  0;
  int Prev_Left =   0;
  int Max_Speed =   0;

  class Scuderia_Drivetrain {
    public:
      void Update(){
        Max_Speed = (ps2x.Button(PSB_L1)) ? Charles_Leclerc : Max_Verstappen; //Use L1 to change the Speed
        int Left_Value = ps2x.Analog(PSS_LY); //Read Value from ps2x_Analog
        int Right_Value = ps2x.Analog(PSS_RY);
        
        //Finding Target Speed
        int Left_Target = Target(Left_Value, Max_Speed);
        int Right_Target = Target(Right_Value, Max_Speed);

        //Smooth the Changes in Speed
        Left_Speed = constrain(Smooth(Prev_Left, Left_Target), - Max_Speed, Max_Speed);
        Right_Speed = constrain(Smooth(Prev_Right, Right_Target), - Max_Speed, Max_Speed);

        // After finding the Speed, adjust the Prev Speed for next time
        Prev_Left = Left_Speed;
        Prev_Right = Right_Speed;

        // Set DriveTrain
        Set(Left_Up, Left_Down, Left_Speed);
        Set(Right_Up, Right_Down, Right_Speed);
      }
    
    private:
      int Target(int Value, int Max_Speed){
        if (abs(Value - Origin) < Pit_Zone){
          return 0;
        }
        int Direction = ((Value - Origin) > 0)? -1: 1;

        int Speed = Direction * map(abs(Value-Origin), 0, 127, 0, Max_Speed);
        return Speed;
      }

      int Smooth(int Previous, int Target){
        return Previous + Smooth_Operator * (Target - Previous);
        }

      void Set(int Up_Location, int Down_Location, int Speed){
        if (Speed > 0){
          pwm.setPWM (Down_Location, 0, 0);
          pwm.setPWM (Up_Location, 0, Speed);
        } else if (Speed < 0){
          pwm.setPWM (Up_Location, 0, 0);
          pwm.setPWM (Down_Location, 0, abs(Speed));
        } else {
          pwm.setPWM (Up_Location,0,0);
          pwm.setPWM (Down_Location, 0, 0);
        }
      }
  }; 
}
Drivetrain::Scuderia_Drivetrain Sainz;

inline void Setup_Drivetrain(){
  pwm.setPWM (Drivetrain::Left_Up ,0,0);
  pwm.setPWM (Drivetrain::Left_Down ,0,0);
  pwm.setPWM (Drivetrain::Right_Up ,0,0);
  pwm.setPWM (Drivetrain::Right_Down ,0,0);
  
}
inline void Drive(){
  Sainz.Update(); //Sainz = Name of the Drivetrain
}
