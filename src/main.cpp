/*
Toto jest program od Kuby Šlofa, který je přepsán pro robota Udes k soutěži Roadside.

Robot odtlačí kamion a vrátí se do startovní zóny.

*/

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

enum Side
{
  REDSIDE,
  BLUESIDE
};
Side side = REDSIDE;


bool baterry_loaded = false;

void ColisionDetector(){
  while (true)
  {
    if (man.ultrasound(0).measure() > 0 && man.ultrasound(0).measure() < 400)
    {
      enemy = BACK;
      //Serial.println("enemy front");
    }
    if (man.ultrasound(1).measure() > 0 && man.ultrasound(1).measure() < 400)
    {
      enemy = FRONT;
      //Serial.println("enemy back");
    }
    if(man.ultrasound(1).measure() >= 400 && man.ultrasound(0).measure() >= 400)
    {
      enemy = NO;
      //Serial.println("no enemy");
    }
  }
}

void EnemyStandingInFront(){

}


void setup()
{
  // Get the manager instance as a singleton
  auto &man = rb::Manager::get();
  // Install the manager
  man.install();
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);


  // while (true)
  // {
  //   if (Serial.available() > 0)
  //   {
  //     String data = Serial.readStringUntil('\n');
  //     if (data == "ready")
  //     {
  //       man.leds().green(true);
  //       break;
  //     }
  //   }
  //   delay(10);
  // }



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
  std::thread t1(ColisionDetector);


  // startovaci tlacitko
  while (true)
  {
    if (man.buttons().up() == 1)
    {
      break;
    }

    delay(10);
  }


  ///////////////////////////////////////////////////////////////////////
  /////////////////  START OF THE PROGRAM ///////////////////////////////
    BackwardUntillWall();
    Backward(1000, 550);
    StopMotors();
    side == REDSIDE ? TurnLeft(85) : Turn(85);
    Straight(1000, 1300, 20000);
    StopMotors();
    Backward(1000, 1200);
    side == REDSIDE ? Turn(90) : TurnLeft(90);
    BackwardUntillWall();

  t1.join();
}

void loop()
{
  // Serial.print("L: ");
}