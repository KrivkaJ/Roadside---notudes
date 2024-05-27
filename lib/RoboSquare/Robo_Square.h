#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>

using namespace lx16a;
static SmartServoBus servoBus;
auto &man = rb::Manager::get(); // needs to be there to work man.sometning
// r motor 3
//  l motor 2
double mm_to_ticks = 0.215;
int wheel_base = 150;
int last_ticks_M4 = 0;
int last_ticks_M1 = 0;
int currenrt_x_pos = 0;
int last_x_pos = 0;
// calculates angle for left klepeto

//vzdalenosti krabicek a baterek 
int Baterry_1 = 1450; // distance to Battery in mm 
int Baterry_2 = 1450 - 1*65;
int Baterry_3 = 1450 - 2*65;
int Baterry_4 = 1450 - 3*65;


int Box_1 = 1990;

int Box_2 = 1990 - 1*200;

int Box_3 = 1990 - 2*200;

int Box_4 = 1990 - 3*200;

int Box_5 = 1990 - 4*200;

int Box_6 = 1990 - 5*200;

int Box_7 = 1990 - 6*200;

int Box_8 = 1990 - 7*200;




Angle left_angle(Angle angle)
{
  angle = 240_deg - angle;
  return angle;
}
struct klepeto
{
  int id = 4;
  void move()
  {
    // tady je kod co pohnek klepetem
  }
  int position()
  {
    // returns position of klepeto
    int position = 0;
    return position;
  }
};
struct arm
{
  void Drivemode()
  {
    // puts the arm in drive mode
    // stupid servos position is from<-2;2>
    man.stupidServo(0).setPosition(0);
    man.stupidServo(1).setPosition(2); // or -2 needs to be tested
    man.stupidServo(2).setPosition(0); // or -2 needs to be tested
  }
  void GrabBaterry()
  {
    man.stupidServo(0).setPosition(2);
    man.stupidServo(1).setPosition(1); // just random needs to be tested
    man.stupidServo(2).setPosition(0);
  }
  void ReleaseBattery()
  {
    man.stupidServo(0).setPosition(-2);
    man.stupidServo(1).setPosition(1); // just random needs to be tested
    man.stupidServo(2).setPosition(2); // or -2 needs to be tested
  }
};

void arc_right(int angle, int radius)
{
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  auto &man = rb::Manager::get();
  double inner_lenght = (((2 * PI * radius) / 360) * angle) / mm_to_ticks;
  double outer_lenght = (((2 * 3.14 * (radius + wheel_base)) / 360) * angle) / mm_to_ticks;
  Serial.println(inner_lenght);
  int outer_sped = 3200;
  int inner_speed = -(outer_sped * inner_lenght) / outer_lenght;
  Serial.println(inner_speed);
  int tics_M1 = 0;
  int tics_M4 = 0;
  Serial.println(outer_lenght);
  while ((inner_lenght > tics_M4) && (outer_lenght > tics_M1))
  { ////inner_lenght < (tics_M1*mm_to_ticks)
    man.motor(rb::MotorId::M1).speed(-outer_sped);
    man.motor(rb::MotorId::M4).speed(-inner_speed);
    man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor &info)
                                           {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position(); });
    man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor &info)
                                           {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position(); });
    delay(10);
  }
  // man.motor(rb::MotorId::M1).speed(0);
  // man.motor(rb::MotorId::M4).speed(0);
}
void Straight(int speed, int distance,int timeout)
{

  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int time = 0;
  int ticks_M1 = 0;
  int last_ticks_M1 = 0;
  int ticks_M4 = 0;
  distance = distance / mm_to_ticks;
  //Serial.println(distance);
  while (ticks_M1 < distance && time < timeout)
  { //(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(-speed);
    man.motor(rb::MotorId::M4).speed(speed);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M4 =  info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M1 =   -info.position(); });

    delay(10);
    time = time + 10;
  
    currenrt_x_pos =  currenrt_x_pos+(ticks_M1-last_ticks_M1)*mm_to_ticks;
    last_ticks_M1 = ticks_M1;
    //Serial.println(currenrt_x_pos);
  }
  // man.motor(rb::MotorId::M1).speed(0);
  // man.motor(rb::MotorId::M4).speed(0);
}
/**
 * Controls the movement of a robot in an arc to the right.
 *
 * @param angle: an integer representing the angle of the arc in degrees
 * @param radius: an integer representing the radius of the arc in millimeters
 *
 * @return None
 */
void arc_left(int angle, int radius)
{
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  auto &man = rb::Manager::get();
  double inner_lenght = (((2 * PI * radius) / 360) * angle) / mm_to_ticks;
  double outer_lenght = (((2 * 3.14 * (radius + wheel_base)) / 360) * angle) / mm_to_ticks;
  Serial.println(inner_lenght);
  int outer_sped = -3200;
  int inner_speed = -(outer_sped * inner_lenght) / outer_lenght;
  Serial.println(inner_speed);
  int tics_M1 = 0;
  int tics_M4 = 0;
  Serial.println(outer_lenght);
  while ((inner_lenght > tics_M1) && (outer_lenght > tics_M4))
  { ////inner_lenght < (tics_M1*mm_to_ticks)
    man.motor(rb::MotorId::M4).speed(-outer_sped);
    man.motor(rb::MotorId::M1).speed(-inner_speed);
    man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor &info)
                                           {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor &info)
                                           {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position(); });
    delay(10);
  }
  // man.motor(rb::MotorId::M4).speed(0);
  // man.motor(rb::MotorId::M1).speed(0);
}
// test????
// needs to start from at least 100 speed_from!!!!!
void Acceleration(int speed_from, int speed_to, int distance_mm)
{
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  double distance_ticks = distance_mm / mm_to_ticks;
  double acc_const = speed_to / distance_ticks;
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  int error = 0;
  while ((ticks_M1 < distance_ticks) && (ticks_M4 < distance_ticks))
  {
    error = 10 * (ticks_M1 - ticks_M4);
    man.motor(rb::MotorId::M1).speed(-(acc_const * ticks_M1 + speed_from - error));
    man.motor(rb::MotorId::M4).speed(acc_const * ticks_M4 + speed_from + error);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = -info.position(); });

    delay(10);
  }
}
void measuring()
{
  int ticks_M4 = 0;
  while (true)
  {
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            Serial.println( info.position());
            ticks_M4 = info.position(); });
    delay(100);
  }
}
void Turn(int angle)
{
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  int distance = ((PI * wheel_base) / 360) * angle / mm_to_ticks;
  while (distance > ticks_M4)
  {
    man.motor(rb::MotorId::M1).speed(500);
    man.motor(rb::MotorId::M4).speed(500);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = -info.position(); });

    delay(10);
  }
  man.motor(rb::MotorId::M4).speed(0);
  man.motor(rb::MotorId::M1).speed(0);
}
void TurnLeft(int angle)
{
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  int distance = ((PI * wheel_base) / 360) * angle / mm_to_ticks;
  while (distance > ticks_M4)
  {
    man.motor(rb::MotorId::M1).speed(-500);
    man.motor(rb::MotorId::M4).speed(-500);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( -info.position());//"M4: position:%d\n",
            ticks_M4 = -info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = info.position(); });

    delay(10);
  }
  man.motor(rb::MotorId::M4).speed(0);
  man.motor(rb::MotorId::M1).speed(0);
}

enum klepeta_state
{
  full_closed,
  triangle,
  open,
  grab_by_wall,
  grab_truck
};
struct klepeta
{
  klepeta_state last_state = full_closed;

  void Move(klepeta_state state)
  {

    if (state == full_closed)
    {
      servoBus.setAutoStop(0, false);
      servoBus.setAutoStop(1, false);
      servoBus.set(1, left_angle(90_deg));
      delay(1000);//tested
      servoBus.set(0, 0_deg);
      delay(1000);//tested
      servoBus.set(1, left_angle(3_deg));
      last_state = full_closed;
    }
    /////////////////////////////////////////
    if (state == triangle)
    {
      if (last_state == full_closed)
      {
        servoBus.setAutoStop(0, false);
        servoBus.setAutoStop(1, false);
        servoBus.set(1, left_angle(90_deg));
        delay(1000);
        servoBus.set(0, 56_deg);
        delay(1000);
        servoBus.set(1, left_angle(56_deg));
        delay(1000);
      }
      else
      {
        servoBus.setAutoStop(0, true);
        servoBus.setAutoStop(1, true);
        for (int i = 0; i < 20; i++)
        {
        servoBus.set(1, left_angle(56_deg));
        servoBus.set(0, 56_deg);
        delay(100);
        }
        
        
        delay(100);
      }
      last_state = triangle;
    }
    /////////////////////////////////////////////////////
    if (state == open)
    {
      servoBus.setAutoStop(0, false);
      servoBus.setAutoStop(1, false);
      if (last_state == full_closed)
      {
        servoBus.set(1, left_angle(120_deg));
        delay(1000);//tested
        servoBus.set(0, 120_deg);
        delay(1200); // wait for the door to open completely
      }
      else{
        servoBus.set(1, left_angle(120_deg));
        servoBus.set(0, 120_deg);
        delay(1000);//tested

      }
      last_state=open;
    }
    ////////////////////////////////////////////////////



  }
};
//robot couva po urcity cas 
//pouziti na dojeti ke zdi 
// duration v ms 
void Couvani(int duration){
int time = 0;
  while(time<duration){
    man.motor(rb::MotorId::M1).speed(1000);
    man.motor(rb::MotorId::M4).speed(-1000);
    delay(10);
    time+=10;
  }
}
void read(){
  while(true){
     int number = Serial.parseInt();
     Serial.println(number);

  }
}

void StraightCustom(int speed, int distance, int left, int right, int timeout)
{

  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int time = 0;
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  distance = distance / mm_to_ticks;
  Serial.println(distance);
  while (ticks_M1 < distance && time < timeout)
  { //(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(-speed-left);
    man.motor(rb::MotorId::M4).speed(speed+right);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M4 =  info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M1 =   -info.position(); });

    delay(10);
    time = time+10;
  }
  // man.motor(rb::MotorId::M1).speed(0);
  // man.motor(rb::MotorId::M4).speed(0);
}


void BackwardCustom(int speed, int distance, int left, int right)
{

  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  distance = distance / mm_to_ticks;
  Serial.println(distance);
  while (ticks_M1 < distance)
  { //(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(speed+left);
    man.motor(rb::MotorId::M4).speed(-speed-right);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M4 =  -info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M1 =   info.position(); });

    delay(10);
  }
  // man.motor(rb::MotorId::M1).speed(0);
  // man.motor(rb::MotorId::M4).speed(0);
}
void Backward(int speed, int distance)
{

  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int ticks_M1 = 0;
  int ticks_M4 = 0;
  distance = distance / mm_to_ticks;
  Serial.println(distance);
  while (ticks_M1 < distance)
  { //(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(speed);
    man.motor(rb::MotorId::M4).speed(-speed);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M4 =  -info.position(); });
    man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M1 =   info.position(); });

    delay(10);
  }
  // man.motor(rb::MotorId::M1).speed(0);
  // man.motor(rb::MotorId::M4).speed(0);
}
void BackwardUntillWall(){
  while (man.buttons().right() == 0 || man.buttons().left() == 0)
  { //(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(2000);
    man.motor(rb::MotorId::M4).speed(-2000);
    delay(10);
  }
  man.motor(rb::MotorId::M1).speed(0);
  man.motor(rb::MotorId::M4).speed(0);
}
