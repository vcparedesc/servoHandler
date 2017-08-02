
/*  Handling several servomotors for mcu control

    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef _servohandler_h_
#include "servoHandler.hpp"
#include <vector>
#include <assert.h>

using namespace std;

template <typename T> inline void swapper(T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

servoHandler::servoHandler(int nServos, vector<int> indexed_list, float min_ms, float max_ms) :  MIN_ms(min_ms), MAX_ms(max_ms), iterator(0), nServos(nServos) {

  // Checking that the dimensions of angle list wrt nServos
  assert(nServos == indexed_list.size());
  index_vector.resize(nServos);
  fixed_index_vector.resize(nServos);
  time_vector.resize(nServos);
  angle_vector.resize(nServos);

  index_vector = indexed_list;
  fixed_index_vector = indexed_list;
}

int servoHandler::setAngles(vector<float> angles) {
  angle_vector = angles;

  for(int i = 0; i < nServos; i++) {
    time_vector[i] = MIN_ms + (MAX_ms - MIN_ms) * (angle_vector[i] / 180.0);
    if(time_vector[i] < MIN_ms || time_vector[i] > MAX_ms) {
      return -1;
    }
  }

  sortTimes();
  return 0;
}

int servoHandler::setTimes(vector<float> times) {
  time_vector = times;

  for(int i = 0; i < nServos; i++) {
    angle_vector[i] = (time_vector[i] - MIN_ms) / (MAX_ms - MIN_ms) * 180;
    if(angle_vector[i] > 180 || angle_vector[i] < 0) {
      return -1;
    }
  }

  sortTimes();
  return 0;
}

float servoHandler::popAngle() {
  if(iterator <= nServos - 1) {
    return angle_vector[iterator];
  } else {
    return -1;
  }
}

float servoHandler::popTime() {
  if(iterator <= nServos - 1) {
    return time_vector[iterator];
  } else {
    return -1;
  }
}

int servoHandler::popPin() {
  if(iterator <= nServos - 1) {
    return index_vector[iterator];
  }
}

servoData servoHandler::popServo() {
  servoData sData;
  static float oldTime = 0;

  sData.angle = popAngle();
  if(iterator != 0) {
    sData.time = popTime() - oldTime;
  }else {
    sData.time = popTime();
  }
  oldTime = popTime();
  sData.pin = popPin();

  iterator = (iterator < nServos - 1 ? ++iterator : 0);
  return sData;
}

int servoHandler::sortTimes() {
  index_vector = fixed_index_vector;
  for(int i = 0; i < nServos; i++) {
    for(int k = i + 1; k < nServos; k++) {
      if(time_vector[i] > time_vector[k]) {
        swapper(time_vector[i], time_vector[k]);
        swapper(index_vector[i], index_vector[k]);
        swapper(angle_vector[i], angle_vector[k]);
      }
    }
  }
  iterator = 0;
  return 0;
}

int servoHandler::setPins(vector<int> indexed_list) {
  fixed_index_vector = indexed_list;
  return 0;
}

int servoHandler::reset() {
  iterator = 0;
  return 0;
}

#define _servohandler_h_
#endif
