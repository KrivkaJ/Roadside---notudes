#include<Robo_square.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
klepeta klepeto;
//robot goes to first position 
void StopMotors(){
  rb::Manager::get().motor(rb::MotorId::M1).speed(0);
  rb::Manager::get().motor(rb::MotorId::M2).speed(0);
  rb::Manager::get().motor(rb::MotorId::M3).speed(0);
  rb::Manager::get().motor(rb::MotorId::M4).speed(0);
}
void MoveToGrabBaterry(){
  Backward(200,30);
  Straight(200,30,3000);
  
}
enum Side {
  REDSIDE,
  BLUESIDE
};
enum BoxColor{
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


void BoxColorGetter(){
  int ticks_M4 = 0;
  int ticks_M1 = 0;
  double distance_cm = 0; 
  bool box1 = 0;
  bool box2 = 0;
  bool box3 = 0;
  bool box4 = 0;
  bool box5 = 0;
  bool box6 = 0;
  bool box7 = 0;
  bool box8 = 0;

  while (true)
  {
   man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M4 =  info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M1 =   -info.position(); });
  delay(50);
  distance_cm = ticks_M1*mm_to_ticks;
  distance_cm = round(distance_cm);

  if (distance_cm > Box_1 && box1 == 0)
  {
    Serial.print("1");
    Serial.println("givecolor");
    
    box1 = 1;
  }
  if (distance_cm > Box_2 && box2 == 0)
  {
    Serial.print("2");
    Serial.println("givecolor");
    box2 = 1;
  }
  if (distance_cm > Box_3 && box3 == 0)
  {
    Serial.print("3");
    Serial.println("givecolor");
    box3 = 1;
  }
  if (distance_cm > Box_4 && box4 == 0)
  {
    Serial.print("4");
    Serial.println("givecolor");
    box4 = 1;
  }
  if (distance_cm > Box_5 && box5 == 0)
  {
    Serial.print("5");
    Serial.println("givecolor");
    box5 = 1;
  }
  if (distance_cm > Box_6 && box6 == 0)
  {
    Serial.print("6");
    Serial.println("givecolor");
    box6 = 1;
  }
  if (distance_cm > Box_7 && box7 == 0)
  {
    Serial.print("7");
    Serial.println("givecolor");
    box7 = 1;
  }
  if (distance_cm > Box_8 && box8 == 0)
  {
    Serial.print("8");
    Serial.println("givecolor");
    box8 = 1;
  }
 // Serial.println(distance_cm);
  }
  
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

  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27);
  servoBus.setAutoStopParams(par);
  servoBus.setAutoStop(0, false);

  //   while (true)
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

std::thread t1(BoxColorGetter);
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
  if (man.buttons().on()==1)
  {
    break;
  }
  
    delay(10);
}

  //startovaci tlacitko
  while (true)
  {
    if (man.buttons().up() == 1)
    {
      break;
    }

    delay(10);
  }
  if(side == BLUESIDE){
  man.stupidServo(1).setPosition(1.4); 
  man.stupidServo(0).setPosition(-2);//90 deg left
  man.stupidServo(2).setPosition(0);//pozice magnetu pro brani baterek
  delay(1000);
  /////////////////////////////////////////////////
  Straight(1500,Baterry_1,10000);
  StopMotors();
  ////////////////////////////////dojede k prvni baterce
  man.stupidServo(1).disable();
  delay(1000);
  MoveToGrabBaterry();
  man.stupidServo(1).setPosition(1.55);//zvedne rameno 
  delay(1000);
  man.stupidServo(0).setPosition(2);//otoci se ramenem na drohou stranu 
  Straight(1000,Box_1-currenrt_x_pos,8000);
  StopMotors();
  man.stupidServo(2).setPosition(2);//pozice magnetu pro pousteni baterek

  }
  if (side == REDSIDE){
  man.stupidServo(1).setPosition(1.4); 
  man.stupidServo(0).setPosition(2);//90 deg right
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
  // if (color == "red"){
  //   Box_1_c = RED;
  // }
  // else if (color == "blue"){
  //   Box_1_c = BLUE;
  // }
  
  man.stupidServo(2).setPosition(2);//pozice magnetu pro pousteni baterek 
   ////////////////////////////////////////prvni baterka  
   delay(500);
BackwardUntillWall();
  }



   









t1.join();

}
void loop()
{
  // Serial.print("L: ");
}