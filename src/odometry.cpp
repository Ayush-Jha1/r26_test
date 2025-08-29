#include "odometry.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <iterator>
#include <numeric>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

Odometry::Odometry(double wheel_radius, double rpm)
    : radius(wheel_radius), rpm(rpm) {
  // Linear velocity (m/s) =(wheel circumference * revolutions per second)
  double rps = rpm / 60.0;
  linear_vel = 2 * M_PI * radius * rps;
}

double Odometry::distance(int x1, int y1, int x2, int y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Odometry::angle(int x1, int y1, int x2, int y2) {
  // atan2 returns radians, convert to degrees
  return atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
}

MotionCommand Odometry::computeCommands(vector<pair<int, int>> &path) {

  MotionCommand res = {0.0, 0.0}; // store total time and angle traversed

 /* Implement you odometry logic here */ 
 
  if (path.size() < 2) {
    return res; // No movement needed
  }
  
  double totalTime = 0.0;
  double totalAngle = 0.0;
  
  // Calculate total distance and time
  for (size_t i = 1; i < path.size(); i++) {
    int x1 = path[i-1].first;
    int y1 = path[i-1].second;
    int x2 = path[i].first;
    int y2 = path[i].second;
    
    // Calculate distance for this segment (assuming 1 meter per grid cell)
    double segmentDistance = distance(x1, y1, x2, y2);
    
    // Calculate time for linear movement
    double segmentTime = segmentDistance / linear_vel;
    totalTime += segmentTime;
    
    // Calculate absolute angle for each segment and add to total
    double segmentAngle = abs(angle(x1, y1, x2, y2));
    totalAngle += segmentAngle;
  }
  
  res.time_sec = totalTime;
  res.angle_deg = totalAngle;

  return res;
}
