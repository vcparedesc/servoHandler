#include "servoHandler.hpp"
#include <iostream>

using namespace std;

float IndexTraj[] = {90.0, 91.39, 92.79, 94.19, 95.59, 96.98, 98.37, 99.76, 101.15, 102.53, 103.9, 105.27, 106.63, 107.99, 109.34, 110.68, 112.01, 113.34, 114.65, 115.96, 117.25, 118.54, 119.81, 121.07, 122.32, 123.55, 124.78, 125.98, 127.18, 128.36, 129.52, 130.67, 131.8, 132.91, 134.01, 135.09, 136.15, 137.2, 138.22, 139.22, 140.21, 141.18, 142.12, 143.04, 143.95, 144.83, 145.69, 146.52, 147.34, 148.13, 148.9, 149.64, 150.36, 151.06, 151.73, 152.38, 153.0, 153.6, 154.17, 154.72, 155.24, 155.73, 156.2, 156.64, 157.06, 157.44, 157.81, 158.14, 158.45, 158.72, 158.98, 159.2, 159.4, 159.57, 159.71, 159.82, 159.9, 159.96, 159.99, 159.99, 159.97, 159.91, 159.83, 159.72, 159.58, 159.41, 159.22, 159.0, 158.75, 158.47, 158.16, 157.83, 157.47, 157.09, 156.68, 156.24, 155.77, 155.28, 154.76, 154.22, 153.65, 153.05, 152.43, 151.78, 151.11, 150.42, 149.7, 148.96, 148.19, 147.4, 146.59, 145.75, 144.9, 144.02, 143.12, 142.19, 141.25, 140.29, 139.3, 138.3, 137.28, 136.24, 135.18, 134.1, 133.0, 131.89, 130.76, 129.61, 128.45, 127.27, 126.08, 124.87, 123.65, 122.42, 121.17, 119.91, 118.64, 117.36, 116.06, 114.76, 113.44, 112.12, 110.79, 109.45, 108.1, 106.74, 105.38, 104.01, 102.64, 101.26, 99.87, 98.49, 97.09, 95.7, 94.3, 92.91, 91.51, 90.11};

float ThumbTraj[] = {90.0, 90.59, 91.19, 91.79, 92.39, 92.99, 93.59, 94.18, 94.77, 95.37, 95.96, 96.54, 97.13, 97.71, 98.29, 98.86, 99.43, 100.0, 100.56, 101.12, 101.68, 102.23, 102.77, 103.31, 103.85, 104.38, 104.9, 105.42, 105.93, 106.44, 106.93, 107.43, 107.91, 108.39, 108.86, 109.32, 109.78, 110.22, 110.66, 111.09, 111.52, 111.93, 112.33, 112.73, 113.12, 113.49, 113.86, 114.22, 114.57, 114.91, 115.24, 115.56, 115.87, 116.17, 116.45, 116.73, 117.0, 117.25, 117.5, 117.73, 117.96, 118.17, 118.37, 118.56, 118.74, 118.9, 119.06, 119.2, 119.33, 119.45, 119.56, 119.65, 119.74, 119.81, 119.87, 119.92, 119.96, 119.98, 119.99, 119.99, 119.98, 119.96, 119.92, 119.88, 119.82, 119.74, 119.66, 119.57, 119.46, 119.34, 119.21, 119.07, 118.91, 118.75, 118.57, 118.38, 118.18, 117.97, 117.75, 117.52, 117.27, 117.02, 116.75, 116.48, 116.19, 115.89, 115.58, 115.26, 114.94, 114.6, 114.25, 113.89, 113.52, 113.15, 112.76, 112.37, 111.96, 111.55, 111.13, 110.7, 110.26, 109.81, 109.36, 108.9, 108.43, 107.95, 107.46, 106.97, 106.48, 105.97, 105.46, 104.94, 104.42, 103.89, 103.36, 102.82, 102.27, 101.72, 101.17, 100.61, 100.04, 99.48, 98.91, 98.33, 97.75, 97.17, 96.59, 96.0, 95.41, 94.82, 94.23, 93.63, 93.04, 92.44, 91.84, 91.24, 90.64, 90.04};

float OtherTraj[] = {10.0, 10.05, 10.23, 10.53, 10.95, 11.49, 12.14, 12.92, 13.8, 14.8, 15.92, 17.14, 18.47, 19.91, 21.45, 23.09, 24.84, 26.68, 28.61, 30.63, 32.74, 34.94, 37.21, 39.56, 41.98, 44.47, 47.03, 49.65, 52.32, 55.04, 57.82, 60.64, 63.49, 66.38, 69.3, 72.25, 75.21, 78.19, 81.19, 84.19, 87.18, 90.18, 93.17, 96.14, 99.1, 102.04, 104.94, 107.82, 110.66, 113.45, 116.21, 118.91, 121.56, 124.15, 126.67, 129.13, 131.52, 133.84, 136.07, 138.23, 140.3, 142.28, 144.17, 145.97, 147.66, 149.26, 150.76, 152.15, 153.43, 154.6, 155.66, 156.61, 157.44, 158.16, 158.76, 159.24, 159.61, 159.85, 159.98, 159.98, 159.87, 159.63, 159.28, 158.8, 158.21, 157.5, 156.68, 155.74, 154.69, 153.53, 152.25, 150.87, 149.38, 147.8, 146.11, 144.32, 142.44, 140.46, 138.4, 136.25, 134.02, 131.71, 129.33, 126.87, 124.35, 121.76, 119.12, 116.42, 113.67, 110.88, 108.04, 105.17, 102.27, 99.34, 96.38, 93.41, 90.42, 87.42, 84.42, 81.43, 78.43, 75.45, 72.48, 69.54, 66.61, 63.72, 60.86, 58.04, 55.26, 52.53, 49.86, 47.23, 44.67, 42.18, 39.75, 37.39, 35.11, 32.91, 30.8, 28.77, 26.83, 24.98, 23.23, 21.58, 20.03, 18.58, 17.24, 16.01, 14.89, 13.88, 12.98, 12.2, 11.54, 10.99, 10.56, 10.25, 10.06, 10.0};

servoHandler *servoManager;

int main(int argc, char **argv) {
  vector<int> servo_pins(3,0);
  vector<float> angles(3,0);
  servoData servo;
  int pointIdx = 0;
  bool isFinished = false;

  servo_pins[0] = 13;
  servo_pins[1] = 14;
  servo_pins[2] = 15;

  servoManager = new servoHandler(3, servo_pins, 1, 2, 2);

  for(int k = 0; k < 2; k++) {
    for(int i = 0; i < 158 - 1; i++) {
      angles[0] = IndexTraj[pointIdx];
      angles[1] = ThumbTraj[pointIdx];
      angles[2] = OtherTraj[pointIdx];

      servoManager->setAngles(angles);

      if(pointIdx < 158 - 1) {
        pointIdx++;
      }else{
        pointIdx = 0;
      }
      // Starting Servo sequence
      servoManager->reset();
      isFinished = false;
      servo = servoManager->popServo();
      // Starting first timer

      // (Second Timer) Simulating timer calls:
      do{

        int nz = servoManager->nZeroTimeServos();
        for(int ss = 0; ss < nz; ss++) {
          cout<<"servo.pin: "<<servo.pin<<endl;
          cout<<"servo.time (elapsed): "<<servo.time<<endl;
          if(ss < nz - 1) {
            servo = servoManager->popServo();
          }
        }

        if(!servo.isLastServo) {
          servo = servoManager->popServo();
        } else {
          isFinished = true;
        }
        char x;
        cin>> x;
      }while(!isFinished);
    }
  }
  return 0;
}
