#include "Sphere.h"
#include "Ray.h"
#include "cmath"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d o = this->center;
  double a = d.dot(d);
  double b = 2 * d.dot(e-o);
  double c = (e-o).dot(e-o) - pow(this->radius,2);
  double deta = pow(b,2) - 4 * a * c;
  if(deta<0){
    return false;
  }
  else if(deta == 0){
    t = -b / 2 * a;
  }
  else{
    t = std::min((-b - pow(deta,0.5))/ (2.0 * a),(-b + pow(deta,0.5))/ (2.0 * a));
    if(t < min_t){
      t = std::max((-b - pow(deta,0.5))/ (2.0 * a),(-b + pow(deta,0.5))/ (2.0 * a));
    }
    if(t<min_t){
      return false;
    }
  }
    Eigen::Vector3d i = e + t * d;
    n = (i - o).normalized();
    return true;
  ////////////////////////////////////////////////////////////////////////////
}

