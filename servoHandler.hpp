#include <vector>
using namespace std;

struct servoData {
  float angle;
  float time;
  int pin;
};


class servoHandler {
  // I can foresee that some servos might have different signal time   // ranges, but for now i am not considering that case.
public:
  servoHandler(int nServos, vector<int> indexed_list, float min_ms, float max_ms);
  ~servoHandler() {};
private:
  int sortTimes();
  float popAngle();
  float popTime();
  int popPin();

  // Variables
  vector<float> time_vector; // Saves activation time
  vector<float> angle_vector; // saves converted angle times
  vector<int> index_vector; // saves the pins for each servo
  vector<int> fixed_index_vector; // Saves original pins
  float MIN_ms, MAX_ms;
  int nServos, iterator;
public:
  int setAngles(vector<float> angles);
  int setTimes(vector<float> times);
  int setPins(vector<int> indexed_list);
  servoData popServo();
  int reset();

  

};
