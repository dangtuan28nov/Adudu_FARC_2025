#pragma once

namespace servo {
  //Locations
  constexpr int Location_Front= 2;
  constexpr int Location_Back = 3;

  //Specifications
  constexpr int Open_Front =   20;
  constexpr int Close_Front = 160;
  constexpr int Open_Back =   160;
  constexpr int Close_Back = 20;

  struct Servo {
    bool Status = false; //False = Close && True = Open
    bool Turning = false; //True = Turning && False = Still
    unsigned long Time = 0;
  };
  Servo Servo_Front, Servo_Back;

  //Values
  long Time_Out = 3000; //3 seconds

  //Blueprints for Servos
  class Scuderia_Servo {
    public:
      void Update() {
        const unsigned long Present_Time = millis();
        Serial.print(Servo_Front.Status);
        Serial.print(" ");
        Serial.println(Servo_Back.Status);

        if (Servo_Front.Turning && Present_Time - Servo_Front.Time >= Time_Out ) {
          Servo_Front.Turning = false;
          pwm.setPWM(Location_Front,0,0);
        }
        if (Servo_Back.Turning && Present_Time - Servo_Back.Time >= Time_Out ) {
          Servo_Back.Turning = false;
          pwm.setPWM(Location_Back,0,0);
        }
        //Check GamePad
        if (ps2x.ButtonPressed(PSB_PAD_UP)) {
          Servo_Front.Status = !Servo_Front.Status;

          if (Servo_Front.Status == true) { //Open
            Set(Location_Front, Open_Front, Servo_Front);

          } else { //Close
            Set(Location_Front, Close_Front, Servo_Front);
          }

        } else if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
          Servo_Back.Status = !Servo_Back.Status;

          if (Servo_Back.Status == true) { //Open
            Set(Location_Back, Open_Back, Servo_Back);

          } else { //Close
            Set(Location_Back, Close_Back, Servo_Back);

          }
        }
      }
    private:
      static void Set(int Location, int Degree, Servo& s){
        int Servo_Value = map(Degree, 0, 180, 150, 600); //Turn Degree into PWM
        pwm.setPWM (Location, 0, Servo_Value);
        s.Turning = true;
        s.Time = millis();
      }
  };
}

servo::Scuderia_Servo Schumacher; //Schumacher = Name of the Servos

inline void Servo_Motor(){
  Schumacher.Update(); //Schumacher = Name of the Servos
}