#include "blinn_phong_shading.h"
#include <Eigen/Core>
#include "first_hit.h"
#include <iostream>
#include <cmath>

Eigen::Vector3d random_dir(const Eigen::Vector3d &seed)
{
  const double pi = std::acos(-1);
  Eigen::Vector3d vector1 = Eigen::Vector3d(127.1, 311.7, 783.089);
  Eigen::Vector3d vector2 = Eigen::Vector3d(269.5, 183.3, 173.542);
  Eigen::Vector2d S = Eigen::Vector2d(seed.dot(vector1), seed.dot(vector2));
  double x1 = sin(S(0)) * 43758.5453123;
  double y1 = sin(S(0)) * 43758.5453123;
  double out_x = x1 - floor(x1);
  double out_y = y1 - floor(y1);
  Eigen::Vector2d uv = Eigen::Vector2d(out_x, out_y);
  double theta = out_x * 2 * pi;
  double r = 0;
  if (out_y > 0.5)
  {
    r = (out_y - 1) * 2;
  }
  else if (out_y < 0.5)
  {
    r = (out_y * 2) - 1;
  }
  double x = sqrt(1 - r * r) * cos(theta);
  double y = sqrt(1 - r * r) * sin(theta);
  double z = r;
  return Eigen::Vector3d(x, y, z);
}

double smooth_step(const double &x)
{
  return 3 * pow(x, 2) + (-2) * pow(x, 3);
}


double perlin_noise(const Eigen::Vector3d &st)
{
  Eigen::Vector3d a = Eigen::Vector3d(floor(st(0)), floor(st(1)), floor(st(2)));
  Eigen::Vector3d b = Eigen::Vector3d(ceil(st(0)), floor(st(1)), floor(st(2)));
  Eigen::Vector3d c = Eigen::Vector3d(ceil(st(0)), ceil(st(1)), floor(st(2)));
  Eigen::Vector3d d = Eigen::Vector3d(floor(st(0)), ceil(st(1)), floor(st(2)));
  Eigen::Vector3d e = Eigen::Vector3d(floor(st(0)), floor(st(1)), ceil(st(2)));
  Eigen::Vector3d f = Eigen::Vector3d(ceil(st(0)), floor(st(1)), ceil(st(2)));
  Eigen::Vector3d g = Eigen::Vector3d(ceil(st(0)), ceil(st(1)), ceil(st(2)));
  Eigen::Vector3d h = Eigen::Vector3d(floor(st(0)), ceil(st(1)), ceil(st(2)));

  Eigen::Vector3d a_dir = random_dir(a);
  Eigen::Vector3d b_dir = random_dir(b);
  Eigen::Vector3d c_dir = random_dir(c);
  Eigen::Vector3d d_dir = random_dir(d);
  Eigen::Vector3d e_dir = random_dir(e);
  Eigen::Vector3d f_dir = random_dir(f);
  Eigen::Vector3d g_dir = random_dir(g);
  Eigen::Vector3d h_dir = random_dir(h);

  Eigen::Vector3d a_seed = st - a;
  Eigen::Vector3d b_seed = st - b;
  Eigen::Vector3d c_seed = st - c;
  Eigen::Vector3d d_seed = st - d;
  Eigen::Vector3d e_seed = st - e;
  Eigen::Vector3d f_seed = st - f;
  Eigen::Vector3d g_seed = st - g;
  Eigen::Vector3d h_seed = st - h;

  double dot_a = a_dir(0) * a_seed(0) + a_dir(1) * a_seed(1) + a_dir(2) * a_seed(2);
  double dot_b = b_dir(0) * b_seed(0) + b_dir(1) * b_seed(1) + b_dir(2) * b_seed(2);
  double dot_c = c_dir(0) * c_seed(0) + c_dir(1) * c_seed(1) + c_dir(2) * c_seed(2);
  double dot_d = d_dir(0) * d_seed(0) + d_dir(1) * d_seed(1) + d_dir(2) * d_seed(2);
  double dot_e = e_dir(0) * e_seed(0) + e_dir(1) * e_seed(1) + e_dir(2) * e_seed(2);
  double dot_f = f_dir(0) * f_seed(0) + f_dir(1) * f_seed(1) + f_dir(2) * f_seed(2);
  double dot_g = g_dir(0) * g_seed(0) + g_dir(1) * g_seed(1) + g_dir(2) * g_seed(2);
  double dot_h = h_dir(0) * h_seed(0) + h_dir(1) * h_seed(1) + h_dir(2) * h_seed(2);

  double alpha_x = smooth_step(a_seed(0));
  double alpha_y = smooth_step(a_seed(1));
  double alpha_z = smooth_step(a_seed(2));

  double ab = dot_a * (1 - alpha_x) + dot_b * alpha_x;
  double dc = dot_d * (1 - alpha_x) + dot_c * alpha_x;
  double ef = dot_e * (1 - alpha_x) + dot_f * alpha_x;
  double hg = dot_h * (1 - alpha_x) + dot_g * alpha_x;

  double abcd = ab * (1 - alpha_y) + dc * alpha_y;
  double efgh = ef * (1 - alpha_y) + hg * alpha_y;
  
  return abcd * (1 - alpha_z) + efgh * alpha_z;
}

Eigen::Vector3d blinn_phong_shading(
    const Ray &ray,
    const int &hit_id,
    const double &t,
    const Eigen::Vector3d &n,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights)
{
  Eigen::Matrix3d m1;
  m1 << 0.04, 0, 0,
      0, 0.04, 0,
      0, 0, 0.04;
  Eigen::Matrix3d m2;
  m2 << 0.2, 0, 0,
      0, 0.2, 0,
      0, 0, 0.2;
  Eigen::Matrix3d m3;
  m3 << 0.03, 0, 0,
      0, 0.03, 0,
      0, 0, 0.03;

  Eigen::Vector3d start = ray.origin + ray.direction * t;
  double background_noise = perlin_noise(m1 * start);
  double sphere_noise = perlin_noise(m2 * start);
  double table_noise = perlin_noise(m3 * start);

  Eigen::Vector3d rgb(0, 0, 0), l_n;
  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  int l_hit;
  double l_max_t;

  rgb += ka;

  double max_t;
  Eigen::Vector3d d;

  for (int i = 0; i < lights.size(); i++)
  {
    Eigen::Vector3d I = lights[i]->I;
    lights[i]->direction(start, d, max_t);
    Ray l_ray;
    l_ray.origin = start;
    l_ray.direction = d;
    Eigen::Vector3d h = (-ray.direction.normalized() + l_ray.direction.normalized()).normalized();
    Eigen::Vector3d kd = objects[hit_id]->material->kd;
    Eigen::Vector3d ks = objects[hit_id]->material->ks;

    double phong = objects[hit_id]->material->phong_exponent;
    double l_max_t;
    bool hit = first_hit(l_ray, 1.0e-5, objects, l_hit, l_max_t, l_n);

    if (hit == false || l_max_t > max_t)
    {
      if (hit_id == 4)
      {
        if (background_noise > 0.1)
        {
          kd = Eigen::Vector3d(0.65, 0.41, 0.16);
        }
        else
        {
          kd = Eigen::Vector3d(0.1, 0.1, 0.1);
        }
      }

      else if (hit_id == 1 || hit_id == 2 || hit_id == 10 || hit_id == 9)
      {
        if (sphere_noise > 0.1)
        {
          kd = Eigen::Vector3d(1.0, 0.94, 0);
        }
      }

      else if (hit_id == 7 || hit_id == 5)
      {
        if (((table_noise > -0.34) && (table_noise < -0.31)) ||
            ((table_noise > -0.28) && (table_noise < -0.25)) ||
            ((table_noise > -0.22) && (table_noise < -0.19)) ||
            ((table_noise > -0.16) && (table_noise < -0.13)) ||
            ((table_noise > -0.10) && (table_noise < -0.07)) ||
            ((table_noise > -0.04) && (table_noise < -0.01)) ||
            ((table_noise > 0.02) && (table_noise < 0.05)) ||
            ((table_noise > 0.08) && (table_noise < 0.11)) ||
            ((table_noise >= 0.14) && (table_noise < 0.17)) ||
            ((table_noise >= 0.20) && (table_noise < 0.23)))
        {
          kd = Eigen::Vector3d(0.3, 0.3, 0.3);
        }
      }
      else if (hit_id == 3 || hit_id == 6)
      {
        if ((table_noise > 0) && (table_noise < 0.05))
        {
          kd = Eigen::Vector3d(1.0, 0.78, 0.93);
        }
      }
      else
      {
        if (sphere_noise > 0.1)
        {
          kd = Eigen::Vector3d(0.68, 1, 0.18);
        }
      }
      Eigen::Vector3d diffuse = fmax(0, n.dot(d)) * (I.array() * kd.array()).matrix();
      Eigen::Vector3d specular = pow(fmax(0, n.dot(h)), phong) * (I.array() * ks.array()).matrix();
      rgb = rgb + diffuse + specular;
    }
  }
  return rgb;
}
