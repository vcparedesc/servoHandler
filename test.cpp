#include "servoHandler.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  vector<int> indexed_list(4,0);
  vector<float> angles(4,0);
  servoData servo;
  indexed_list[0] = 0;
  indexed_list[1] = 1;
  indexed_list[2] = 2;
  indexed_list[3] = 3;

  servoHandler servohandler(4, indexed_list, 0.0,2.0);

  angles[0] = 0;
  angles[1] = 170;
  angles[2] = 10;
  angles[3] = 60;

  cout<<"Ouput: "<<servohandler.setAngles(angles)<<endl;

  for(int i = 0; i < 4; i++) {
    servo = servohandler.popServo();
    cout<<"Servo (pin): "<<servo.pin<<endl;
    cout<<"Angle: "<<servo.angle<<endl;
    cout<<"Time: "<<servo.time<<endl;
  }

  // If the servo pins are changed:
  indexed_list[0] = 4;
  indexed_list[1] = 2;
  indexed_list[2] = 6;
  indexed_list[3] = 7;

  cout<<"Changing the pins of the servomotors"<<endl;
  servohandler.setPins(indexed_list);
  servohandler.setAngles(angles);
  for(int i = 0; i < 4; i++) {
    servo = servohandler.popServo();
    cout<<"Servo (pin): "<<servo.pin<<endl;
    cout<<"Angle: "<<servo.angle<<endl;
    cout<<"Time: "<<servo.time<<endl;
  }


  return 0;
}
