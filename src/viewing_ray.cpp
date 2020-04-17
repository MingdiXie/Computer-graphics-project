#include "viewing_ray.h"
#include <iostream>
void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ray.origin = camera.e;
  double u = camera.width * ((j + 0.5)/width-0.5);
  double v = -camera.height * ((i + 0.5)/height - 0.5);
  ray.direction = u * camera.u + v * camera.v - camera.d * camera.w;
  ////////////////////////////////////////////////////////////////////////////
}

