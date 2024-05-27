#include<Robo_square.h>
#include <iostream>
#include <string>
#include <sstream>
klepeta klepeto;
//robot goes to first position 


void setup()
{
bool found_bear = false;
  std::stringstream ss;
  // Get the manager instance as a singleton
  auto &man = rb::Manager::get();
  // Install the manager
  man.install();
  
  
  //for setting autostop parameters
  SmartServoBus::AutoStopParams par;
  par.max_diff_centideg = 1000;
  par.max_diff_readings = 1;

  // Set the serial communication baud rate to 115200
  Serial.begin(115200);


////////test
//   while (true)
//   {
//     if (man.buttons().up() == 1)
//     {
//       break;
//     }

//     delay(10);
//   }

//   man.stupidServo(0).setPosition(2);//90 deg right
//   man.stupidServo(1).setPosition(1.4); 
//   man.stupidServo(2).setPosition(0);
//   delay(800);
//   //man.stupidServo(1).disable();
//   delay(1000);
//   Straight(2000,1450,10000);
//   man.motor(rb::MotorId::M1).speed(0);
//   man.motor(rb::MotorId::M4).speed(0);
//   ////////////////////////////////
//   delay(1000);
//   man.stupidServo(1).disable();
//   delay(1000);
//   Straight(200,30,3000);
//   Backward(200,30);
//   man.stupidServo(1).setPosition(1.55);
//   delay(1000);
//   man.stupidServo(0).setPosition(-2);
//   delay(1000);
//   Straight(400,500,8000);
//     man.motor(rb::MotorId::M1).speed(0);
//   man.motor(rb::MotorId::M4).speed(0);
//    man.stupidServo(2).setPosition(2);
//    ////////////////////////////////////////prvni baterka 
//    delay(1000);
//    man.stupidServo(2).setPosition(0);
//    man.stupidServo(0).setPosition(2);
//    delay(1000);
//    Backward(400,550);
//    man.stupidServo(1).setPosition(1.4); 
//    man.stupidServo(1).disable();
//    delay(1000);
//   Straight(200,30,3000);
//   Backward(200,30);
//   man.stupidServo(1).setPosition(1.55);
//   delay(1000);
//   man.stupidServo(0).setPosition(-2);
//   delay(1000);
//   Straight(400,450,8000);
//   man.motor(rb::MotorId::M1).speed(0);
//   man.motor(rb::MotorId::M4).speed(0);
//    man.stupidServo(2).setPosition(2);
//    delay(500);
// BackwardUntillWall();



   








//////////endtest 

////////////////////////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////////////

//startovaci tlacitko
  ///////////////////////////////////////////////
  while (true)
  {
    if (man.buttons().up() == 1)
    {
      break;
    }

    delay(10);
  }
/////////////////////////////////////////////  
  // Connecting to the servo bus 
  delay(500);
  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27);
  servoBus.setAutoStopParams(par);
  servoBus.setAutoStop(0, false);
  //servoBus.setAutoStop(1, true);
  //klepeto.Move(full_closed);

////////////////////////////


}
void loop()
{
  // Serial.print("L: ");
}