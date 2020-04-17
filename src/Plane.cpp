#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d normal = this->normal;
  Eigen::Vector3d p = this->point;
  double denom = ray.direction.dot(normal);

  if (denom == 0) return false;

  double numerator = (p-ray.origin).dot(normal);
  t = numerator / denom; 

  if (t < min_t){ return false;}
  else{
    n = normal;
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}


