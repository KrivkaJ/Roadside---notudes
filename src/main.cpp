#include<Robo_square.h>
#include <iostream>
#include <string>
#include <sstream>
klepeta klepeto;
//robot goes to first position 
void StopMotors(){
  rb::Manager::get().motor(rb::MotorId::M1).speed(0);
  rb::Manager::get().motor(rb::MotorId::M2).speed(0);
  rb::Manager::get().motor(rb::MotorId::M3).speed(0);
  rb::Manager::get().motor(rb::MotorId::M4).speed(0);
}
void MoveToGrabBaterry(){
  Straight(200,30,3000);
  Backward(200,30);
}
void setup()
{
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
  while (true)
  {
    if (man.buttons().up() == 1)
    {
      break;
    }

    delay(10);
  }
  man.stupidServo(0).setPosition(2);//90 deg right
  man.stupidServo(1).setPosition(1.4); 
  man.stupidServo(2).setPosition(0);//pozice magnetu pro brani baterek 
  delay(1000);
  //////////////////////////////////konec pripravy
  Straight(1500,Baterry_1,10000);
  StopMotors();
  ////////////////////////////////dojede k prvni baterce 
  man.stupidServo(1).disable();
  delay(1000);
  MoveToGrabBaterry();
  man.stupidServo(1).setPosition(1.55);//zvedne rameno 
  delay(1000);
  man.stupidServo(0).setPosition(-2);//otoci se ramenem na drohou stranu 
  Straight(1000,Box_1-currenrt_x_pos,8000);
  StopMotors();
  //tady se podiva na barvu baterky 
  man.stupidServo(2).setPosition(2);//pozice magnetu pro pousteni baterek 
   ////////////////////////////////////////prvni baterka 

BackwardUntillWall();



   








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