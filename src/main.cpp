#include<Robo_square.h>
#include <iostream>
#include <string>
#include <sstream>
klepeta klepeto;
//robot goes to first position 
void GoToPos1(){
 Acceleration(300, 32000, 400); // default 500
  arc_right(180, 180);
  Straight(32000, 100,4000);
  //servoBus.set(0,90_deg);
  arc_left(168, 150);
  //servoBus.set(0,95_deg);
  Straight(32000, 130,4000);
  Acceleration(32000, 100, 320);
  man.motor(rb::MotorId::M4).speed(0);
  man.motor(rb::MotorId::M1).speed(0);
  klepeto.Move(open);
}

//robot se vraci zpatky od chyceni medveda z poyice 1  
void GoHome1(){
  man.leds().blue(true);
  BackwardCustom(1000,100,0,100);
  Turn(95);
  BackwardUntillWall();
  Straight(1000,20,4000);
  TurnLeft(95);
  BackwardUntillWall();
  StraightCustom(1000,100,0,500,5000);
    Turn(90);
  BackwardUntillWall();
  Straight(2000,150,2000);
  arc_right(90,300);
  Straight(2000,100,2000);
  arc_left(180,170);
  Straight(3000,100,2000);
  while(true){
    delay(100);
  }
}

//robot goes to second position
void GoToPos2(){
klepeto.Move(triangle);
Straight(1000,400,4000);
delay(10);
Turn(90);

BackwardUntillWall();
klepeto.Move(open);
//konec
}
void GoHome2(){
  man.leds().blue(true);
  BackwardUntillWall();
  Straight(1000,20,4000);
  TurnLeft(95);
  BackwardUntillWall();
  StraightCustom(1000,100,0,500,5000);
    Turn(90);
  BackwardUntillWall();
  Straight(2000,150,2000);
  arc_right(90,300);
  Straight(2000,100,2000);
  arc_left(180,170);
  Straight(3000,100,2000);
   while(true){
    delay(100);
  }
}
//robot goes to third position
void GoToPos3() {
Straight(2000,1050,4000);
delay(10);
TurnLeft(90);
Couvani(1500);//upgrade na backbutton
}

void GoHome3(){
  man.leds().blue(true);
  BackwardCustom(1000,400,1100,0);
  BackwardUntillWall();
  TurnLeft(95);
  BackwardUntillWall();
  StraightCustom(1000,100,0,500,5000);
    Turn(90);
  BackwardUntillWall();
  Straight(2000,150,2000);
  arc_right(90,300);
  Straight(2000,100,2000);
  arc_left(180,170);
  Straight(3000,100,2000);
   while(true){
    delay(100);
  }

   while(true){
    delay(100);
  }
}


  int x_distance = 0;//vzdalenost medveda v cm delka 
  int y_distakce = 0;//vzdalenost medveda v cm sirka

void WaitingForBearPosData(){

//ceka na distance to bear 
  while (true)
  {
    if(Serial.available() > 0){
      int num = 9999;
       String data = Serial.readStringUntil('\n');
       const char* daata = data.c_str();
       num = std::atoi(daata);

       if (num !=9999)
       {
         x_distance = num;
        break;
    }
    delay(10);
  }
  //ceka na y distance medveda 
  }
    while (true)
  {
    if(Serial.available() > 0){
      int num = 9999;
       String data = Serial.readStringUntil('\n');
       const char* daata = data.c_str();
       num = std::atoi(daata);

       if (num !=9999)
       {
         y_distakce = num;
        break;
    }
    delay(10);
  }
  }


}



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
  delay(1000);//prodleva pred odstartovanim robota
  klepeto.Move(triangle);//da klepeta do jezdiciho modu 

  GoToPos1();// dojede na prvni pozici  

  
  //posle zpravu do raspberri ze ma dat fotku 
  Serial.println("inposition");

//ceka na zpravu jestli byl nalezen medved
  while (true)
  {
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      if (data == "true")
      {
        found_bear = true;
        break;
      }
      if (data == "false"){
        found_bear = false;
        break;
      }
    }
    delay(10);
  }
  if (found_bear==true){
    //tady bude kod k nalezeni medveda 
    //ceka nez dojdou data z raspberri pi
    WaitingForBearPosData();
// if(y_distakce>=0){
//   Turn(tan(x_distance/y_distakce)* (180.0/3.141592653589793238463));//zatacka doprava
//   Straight(2000,sqrt(y_distakce*y_distakce+x_distance*x_distance)*10);
// }
// if(y_distakce<0){
//   Turn(tan(x_distance/abs(y_distakce))* (180.0/3.141592653589793238463));//zatacka doleva
//   Straight(2000,sqrt(y_distakce*y_distakce+x_distance*x_distance)*10);
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //tady budou komandy pro dojeti pro medveda 
    if (y_distakce>-10){
      StraightCustom(1000, x_distance*10,50,0,10000);//krat 10 protoze je to prevod z cm ma mm
   
      }
      else{
    Straight(1500,250,4000);
    Turn(45);
    Straight(1500,sqrt(y_distakce*y_distakce*2*100),6000);//krat 10 protoze cm na mmv
    TurnLeft(42);
    Straight(2000, (x_distance-y_distakce)*10-250,6000);//krat 10 protoze je to prevod z cm ma mm
       //ted by mel stat u medveda
      }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
  klepeto.Move(triangle);//catching medved 
  GoHome1();
//konec kdyz najde medveda 
  }

  if(found_bear == false){
    GoToPos2();
  }
  /////////
  Serial.println("inposition");
//ceka na zpravu jestli byl nalezen medved
  while (true)
  {
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      if (data == "true")
      {
        found_bear = true;
        break;
      }
      if (data == "false"){
        found_bear = false;
        break;
      }
    }
    delay(10);
  }
if (found_bear == true){

WaitingForBearPosData();
    if (y_distakce<-10){
      StraightCustom(1000, x_distance*10,0,100,5000);//krat 10 protoze je to prevod z cm ma mm
   
      }
      else{
    Straight(1500,250,4000);
    TurnLeft(45);
    Straight(1500,sqrt(y_distakce*y_distakce*2*100),4000);//krat 10 protoze cm na mm
    Turn(42);
    Straight(2000, (x_distance-y_distakce)*10-250,4000);//krat 10 protoze je to prevod z cm ma mm
       //ted by mel stat u medveda
      }
klepeto.Move(triangle);
    GoHome2();

}
   if(found_bear == false){
    klepeto.Move(full_closed);
    GoToPos3();
    klepeto.Move(open);
  }


/////////////////////////////////////////////////////////

  Serial.println("inposition");
//ceka na zpravu jestli byl nalezen medved
  while (true)
  {
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      if (data == "true")
      {
        found_bear = true;
        break;
      }
      if (data == "false"){
        found_bear = false;
        break;
      }
    }
    delay(10);
  }
if (found_bear == true){

WaitingForBearPosData();
    if (y_distakce<-10){
      StraightCustom(1000, x_distance*10,0,50,5000);//krat 10 protoze je to prevod z cm ma mm
   
      }
      else{
    Straight(1500,250,4000);
    TurnLeft(45);
    Straight(1500,sqrt(y_distakce*y_distakce*2*100),4000);//krat 10 protoze cm na mm
    Turn(42);
    Straight(2000, (x_distance-y_distakce)*10-250,4000);//krat 10 protoze je to prevod z cm ma mm
       //ted by mel stat u medveda
      }
klepeto.Move(triangle);
    GoHome3();

}


  
  
  
  
  //klepeto.Move(full_closed);
////////////////////////////


}
void loop()
{
  // Serial.print("L: ");
}