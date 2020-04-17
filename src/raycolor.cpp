#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"


bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  if(num_recursive_calls > 3){
    return false;
  }
  rgb = Eigen::Vector3d(0,0,0);
  int hit_id;
  Eigen::Vector3d n;
  double t;
  if(first_hit(ray,1.0e-5,objects,hit_id,t,n)){
    rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Ray reflect_ray;
    reflect_ray.direction = reflect(ray.direction, n);
    reflect_ray.origin = ray.origin + ray.direction * t;
    Eigen::Vector3d new_rgb;
    if(raycolor(reflect_ray, 1.0e-5, objects, lights, num_recursive_calls+1,new_rgb)){
      rgb += (objects[hit_id]->material->km.array() * new_rgb.array()).matrix();
    }
    return true;
  }
  else{
  return false;
  }  
  ////////////////////////////////////////////////////////////////////////////
}
