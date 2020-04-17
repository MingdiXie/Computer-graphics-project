#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
using namespace std;
using namespace Eigen;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Vector3d aa = get<0>(corners);
  Vector3d bb = get<1>(corners);
  Vector3d cc = get<2>(corners);
  double xa = aa[0], ya = aa[1], za = aa[2];
  double xb = bb[0], yb = bb[1], zb = bb[2];
  double xc = cc[0], yc = cc[1], zc = cc[2];
  double xd = ray.direction[0], yd = ray.direction[1], zd = ray.direction[2];
  double xe = ray.origin[0], ye = ray.origin[1], ze = ray.origin[2];

// Cramer's rule
//   double a = xa-xb;
//   double b = ya-yb;
//   double c = za-zb;
//   double d = xa-xc;
//   double e = ya-yc;
//   double f = za-zc;
//   double g = xd;
//   double h = yd;
//   double i = zd;
//   double j = xa-xe;
//   double k = ya-ye;
//   double l = za-ze;

//   double M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
//   double beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
//   double gama = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
//   t = -(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;

  Matrix3f A;
  A << xa-xb, xa-xc, xd, ya-yb, ya- yc, yd, za-zb, za-zc, zd;
  
  Vector3f jkl;
  jkl << xa-xe, ya-ye, za-ze;
  
  Vector3f solution = A.colPivHouseholderQr().solve(jkl);

  if(solution[0] < 0 || solution[1] < 0 || (solution[0]+solution[1])>1) {return false;}
  else if(solution[2]< min_t) {return false;}
  else{
    t = solution[2];
    Eigen::Vector3d p = aa + solution[0]*(bb-aa) + solution[1]*(cc-aa);
    Eigen::Vector3d l1 = aa - p;
    Eigen::Vector3d l2 = bb - p;
    Eigen::Vector3d norm = l1.cross(l2);
    n = norm / sqrt(pow(norm[0], 2.0)+ pow(norm[1], 2.0)+ pow(norm[2], 2.0)); 
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}


