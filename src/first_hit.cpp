#include "first_hit.h"
#include <iostream>
#include <limits>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool start = false;
  double tempT;
  Eigen::Vector3d tempN;
  t = std::numeric_limits<int>::max();
  for(int i=0;i<objects.size();i++){
    if(objects[i]->intersect(ray, min_t, tempT, tempN)){
      if(tempT < t && tempT > 0){
        t = tempT;
        n = tempN;
        hit_id = i;
        start = true;
      }
    }
  }
  return start;
  ////////////////////////////////////////////////////////////////////////////
}

