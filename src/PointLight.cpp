#include "PointLight.h"
#include <cmath>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  d = p-q;
  max_t = pow(pow(d[0],2) + pow(d[1],2) + pow(d[2],2),0.5);
  d = d.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
