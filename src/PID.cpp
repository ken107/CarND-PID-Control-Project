#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Kd, double Ki) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  p_error = 9999;
  i_error = 0;
  sum_squared_error = 0;
  count = 0;
}

void PID::UpdateError(double cte) {
  d_error = (p_error == 9999) ? 0 : (cte - p_error);
  p_error = cte;
  i_error += cte;
  sum_squared_error += cte*cte;
  count++;
}

double PID::TotalError() {
  return Kp*p_error + Kd*d_error + Ki*i_error;
}

double PID::MeanSquaredError() {
  return sum_squared_error / count;
}
