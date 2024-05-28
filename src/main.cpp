#include <Robo_square.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
klepeta klepeto;
// robot goes to first position
void StopMotors()
{
  rb::Manager::get().motor(rb::MotorId::M1).speed(0);
  rb::Manager::get().motor(rb::MotorId::M2).speed(0);
  rb::Manager::get().motor(rb::MotorId::M3).speed(0);
  rb::Manager::get().motor(rb::MotorId::M4).speed(0);
}
void MoveToGrabBaterry()
{
  Backward(200, 30);
  Straight(200, 30, 3000);
}
enum Side
{
  REDSIDE,
  BLUESIDE
};
enum BoxColor
{
  RED,
  BLUE,
  IDK
};
BoxColor Box_1_c = IDK;
BoxColor Box_2_c = IDK;
BoxColor Box_3_c = IDK;
BoxColor Box_4_c = IDK;
BoxColor Box_5_c = IDK;
BoxColor Box_6_c = IDK;
BoxColor Box_7_c = IDK;
BoxColor Box_8_c = IDK;

Side side = REDSIDE;


BoxColor ReciveData(){
  BoxColor box = IDK;
  while (true)
      {
        if (Serial.available() > 0)
        {
          String data = Serial.readStringUntil('\n');
          if (data == "red")
          {
            box = RED;

            break;
          }
          if (data == "blue")
          {
           box = BLUE;
            break;
          }
        }
        delay(10);
      }
      return box;
} 
void setup()
{
  // Get the manager instance as a singleton
  auto &man = rb::Manager::get();
  // Install the manager
  man.install();
  // for setting autostop parameters
  SmartServoBus::AutoStopParams par;
  par.max_diff_centideg = 1000;
  par.max_diff_readings = 1;
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);

  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27);
  servoBus.setAutoStopParams(par);
  servoBus.setAutoStop(0, false);

  while (true)
  {
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      if (data == "ready")
      {
        man.leds().green(true);
        break;
      }
    }
    delay(10);
  }

  while (true)
  {
    if (man.buttons().up() == 1)
    {
      side = REDSIDE;
      man.leds().yellow(true);
      man.leds().blue(false);
    }
    if (man.buttons().down() == 1)
    {
      side = BLUESIDE;
      man.leds().blue(true);
      man.leds().yellow(false);
    }
    if (man.buttons().on() == 1)
    {
      break;
    }

    delay(10);
  }

  // startovaci tlacitko
  while (true)
  {
    if (man.buttons().up() == 1)
    {
      break;
    }

    delay(10);
  }
  if (side == BLUESIDE)
  {
    man.stupidServo(1).setPosition(1.4);
    man.stupidServo(0).setPosition(-2); // 90 deg left
    man.stupidServo(2).setPosition(0);  // pozice magnetu pro brani baterek
    delay(1000);
    /////////////////////////////////////////////////
    Straight(500, Baterry_1, 30000);
    StopMotors();
    ////////////////////////////////dojede k prvni baterce
    man.stupidServo(1).disable();
    delay(1000);
    MoveToGrabBaterry();
    man.stupidServo(1).setPosition(1.55); // zvedne rameno
    delay(1000);
    man.stupidServo(0).setPosition(2); // otoci se ramenem na drohou stranu
    Straight(1000, Box_1 - currenrt_x_pos, 8000);
    StopMotors();
    man.stupidServo(2).setPosition(2); // pozice magnetu pro pousteni baterek
    delay(500);
  }
  if (side == REDSIDE)
  {
    man.stupidServo(1).setPosition(1.4);
    man.stupidServo(0).setPosition(2); // 90 deg right
    man.stupidServo(2).setPosition(0); // pozice magnetu pro brani baterek
    delay(1000);
    //////////////////////////////////konec pripravy
    Straight(1500, Baterry_1, 10000);
    StopMotors();
    ////////////////////////////////dojede k prvni baterce
    man.stupidServo(1).disable();
    delay(1000);
    MoveToGrabBaterry();
    man.stupidServo(1).setPosition(1.55); // zvedne rameno
    delay(1000);
    man.stupidServo(0).setPosition(-2); // otoci se ramenem na drohou stranu
    Straight(1000, Box_1 - currenrt_x_pos - 150, 8000);
    StopMotors();
    Serial.println("givecolor");
    delay(1000);
    Straight(1000, 150, 3000);
    StopMotors();
    Box_1_c = ReciveData();
    if (Box_1_c == RED)
    {
      man.stupidServo(2).setPosition(2); // pozice magnetu pro pousteni baterek
    }
    if (Box_1_c == BLUE)
    {
      man.leds().blue(true);
      Backward(1000, currenrt_x_pos - Box_2 + 150);
      StopMotors();
      Serial.println("givecolor");
      delay(500);
      Box_2_c = ReciveData();
      if (Box_2_c == RED){
        Straight(1000,150,10000);
        StopMotors();
        man.stupidServo(2).setPosition(2); // pozice magnetu pro pousteni baterek
      }
    }

    ///////////////////////////////////////////////////////////
    // tady se podiva na barvu baterky
    //  if (color == "red"){
    //    Box_1_c = RED;
    //  }
    //  else if (color == "blue"){
    //    Box_1_c = BLUE;
    //  }

    // pozice magnetu pro pousteni baterek
    ////////////////////////////////////////prvni baterka
    delay(500);
    // BackwardUntillWall();
  }
}
void loop()
{
  // Serial.print("L: ");
}