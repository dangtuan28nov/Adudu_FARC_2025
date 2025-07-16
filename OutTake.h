#pragma once

namespace Out_Take{
  //Locations
  constexpr int Location_Front= 2;
  constexpr int Location_Back = 3;

  //Specifications
  constexpr int Open_Front =    10;
  constexpr int Close_Front =   70;
  constexpr int Open_Back =     10;
  constexpr int Close_Back =    70;

  struct Servo_State {
    bool Status = false; //False = Close && True = Open
    bool Turning = false; //True = Turning && False = Still
    unsigned long Time = 0;
  };
  Servo_State Servo_Front, Servo_Back;

  //Values
  long Time_Out = 5000; //5 seconds

  //Blueprints for Servos
  class Scuderia_Servo {
    public:
      static void Update() {
        const unsigned long Present_Time = millis();
        if (Servo_Front.Turning && Present_Time - Servo_Front.Time >= Time_Out ) {
          Servo_Front.Turning = false;
          pwm.setPWM(Location_Front,0,0);
        }
        if (Servo_Back.Turning && Present_Time - Servo_Back.Time >= Time_Out ) {
          Servo_Back.Turning = false;
          pwm.setPWM(Location_Back,0,0);
        }
        if (ps2x.ButtonPressed(PSB_PAD_UP)) {
          Servo_Front.Status = !Servo_Front.Status;
          if (Servo_Front.Status == false) { //Open
            Set(Location_Front, Open_Front, Servo_Front);

          } else if (Servo_Front.Status == true) { //Close
            Set(Location_Front, Close_Front, Servo_Front);
          }
        }
        if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
          Servo_Back.Status = !Servo_Back.Status;
          if (Servo_Back.Status == false) { //Open
            Set(Location_Back, Open_Back, Servo_Back);
          } else if (Servo_Back.Status == true) { //Close
            Set(Location_Back, Close_Back, Servo_Back);
          }
        }
      }
    private:
      static void Set(int Location, int Degree, Servo_State& s){
        s.Turning = true;
        s.Time = millis();
        pwm.setPWM(Location, 0, map(Degree, 0, 180, 150, 600));
      }
  };
}

Out_Take::Scuderia_Servo Schumacher;

inline void Servo_Motor(){
  Schumacher.Update();
}