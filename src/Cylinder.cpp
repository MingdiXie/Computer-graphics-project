#include "Cylinder.h"
#include "Ray.h"
#include <iostream>
#include <vector>
// reference https://github.com/327926791/csc418project/blob/master/src/Cylinder.cpp
#define PI 3.1415926

bool Cylinder::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
// Replace with your code here:
double x0, y0, z0, x1, y1, z1, x3,y3,z3,x4,y4,z4, x, y ,z;
double k1, k2, k3, k4, k5, k6, delta, t1, t2;

//std::cout << "..........hit cylinder....\n";

t = -1;
x0 = ray.origin(0) ;
y0 = ray.origin(1) ;
z0 = ray.origin(2) ;

x1 = ray.direction(0) ;
y1 = ray.direction(1) ;
z1 = ray.direction(2) ;

x3 = p0(0);
y3 = p0(1);
z3 = p0(2);

x4 = p1(0);
y4 = p1(1);
z4 = p1(2);

//std::cout << "x0,y0,z1:" << x0 << " " << y0 << " " << z0<< "\n";
//std::cout << "x1,y1,z1:" << x1 << " " << y1 << " " << z1 << "\n";
//std::cout << "x3,y3,z3:" << x3 << " " << y3 << " " << z3 << "\n";

// parallel y-axis
if (y3 < y4) {
	if (y1 > 0) {  // check if intersect on the bottom face
		t = (y3 - y0) / y1;
		x = t * x1 + x0;
		z = t * z1 + z0;
		//std::cout << "hit bottom face?  t:" << t << " " << x << " "<<y << "\n";
		if (pow((x - x3), 2) + pow((z - z3), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(0, -1, 0);
				return true;
			}
			else
				t = -1;
		}
	}
	else if (y1 < 0) {  // check if intersect on the top face
		t = (y4 - y0) / y1;
		x = t * x1 + x0;
		z = t * z1 + z0;
		//std::cout << "hit top face?  t:" << t << " " << x << " " << y << "\n";
		if (pow((x - x4), 2) + pow((z - z4), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(0, 1, 0);
				//std::cout << "hit:" << n << " t:" << t << "\n";
				return true;
			}
			else
				t = -1;
		}
	}
	if (x1 != 0 && z1 != 0) {  // check if hit the pole
		k1 = x1 / z1;
		k2 = (x1*z0 - x0*z1) / z1;
		k3 = k2 + x3;

		k4 = pow(k1, 2) + 1;
		k5 = 2 * k1*k3 + 2 * z3;
		k6 = pow(k3, 2) + pow(z3, 2) - pow(radius, 2);

		delta = pow(k5, 2) - 4 * k4 * k6;
		//std::cout << "hit pole?  delta:" << delta << "\n";
		if (delta >= 0) {
			z = (k5 + sqrt(delta)) / (2 * k4);
			t1 = (z - z0) / z1;
			z = (k5 - sqrt(delta)) / (2 * k4);
			t2 = (z - z0) / z1;
			if (t1 <= t2) {
				z = (k5 + sqrt(delta)) / (2 * k4);
				x = k1 * z - k2;
				t = t1;
				n = Eigen::Vector3d(x - x3, 0, z - z3);
			}
			else {
				x = k1 * z - k2;
				n = Eigen::Vector3d(x - x3,0, z - z3);
				t = t2;
			}
			y = t * y1 + y0;
			if (y<y3 || y>y4)
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
// parall with x-axis
else if (x3 < x4) {
	if (x1 > 0) {  // check if intersect on the bottom face
		t = (x3 - x0) / x1;
		y = t * y1 + y0;
		z = t * z1 + z0;
		//std::cout << "hit bottom face?  t:" << t << " " << x << " "<<y << "\n";
		if (pow((y - y3), 2) + pow((z - z3), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(-1, 0, 0);
				return true;
			}
			else
				t = -1;
		}
	}
	else if (x1 < 0) {  // check if intersect on the top face
		t = (x4 - x0) / x1;
		y = t * y1 + y0;
		z = t * z1 + z0;
		//std::cout << "hit top face?  t:" << t << " " << x << " " << y << "\n";
		if (pow((y - y4), 2) + pow((z -z4 ), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(1, 0, 0);
				//std::cout << "hit:" << n << " t:" << t << "\n";
				return true;
			}
			else
				t = -1;
		}
	}
	if (y1 != 0 && z1 != 0) {  // check if hit the pole
		k1 = y1 / z1;
		k2 = (y1*z0 - y0*z1) / z1;
		k3 = k2 + y3;

		k4 = pow(k1, 2) + 1;
		k5 = 2 * k1*k3 + 2 * z3;
		k6 = pow(k3, 2) + pow(z3, 2) - pow(radius, 2);

		delta = pow(k5, 2) - 4 * k4 * k6;
		//std::cout << "hit pole?  delta:" << delta << "\n";
		if (delta >= 0) {
			z = (k5 + sqrt(delta)) / (2 * k4);
			t1 = (z - z0) / z1;
			z = (k5 - sqrt(delta)) / (2 * k4);
			t2 = (z - z0) / z1;
			if (t1 <= t2) {
				z = (k5 + sqrt(delta)) / (2 * k4);
				y = k1 * z - k2;
				t = t1;
				n = Eigen::Vector3d(0, y - y3, z - z3);
			}
			else {
				y = k1 * z - k2;
				n = Eigen::Vector3d(0, y - y3, z - z3);
				t = t2;
			}
			x = t * x1 + x0;
			if (x<x3 || x>x4)
				return false;
		}
		else
			return false;
	}
	else
		return false;
}


// parallel z-axis
else if (z3 < z4) {
	if (z1 > 0) {  // check if intersect on the bottom face
		t = (z3 - z0) / z1;
		x = t * x1 + x0;
		y = t * y1 + y0;
		//std::cout << "hit bottom face?  t:" << t << " " << x << " "<<y << "\n";
		if (pow((x - x3), 2) + pow((y - y3), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(0, 0, -1);
				return true;
			}
			else
				t = -1;
		}
	}
	else if (z1 < 0) {  // check if intersect on the top face
		t = (p1(2) - z0) / z1;
		x = t * x1 + x0;
		y = t * y1 + y0;
		//std::cout << "hit top face?  t:" << t << " " << x << " " << y << "\n";
		if (pow((x - x4), 2) + pow((y - y4), 2) <= pow(radius, 2)) {
			// hit
			if (t >= min_t) {
				n = Eigen::Vector3d(0, 0, 1);
				//std::cout << "hit:" << n << " t:" << t << "\n";
				return true;
			}
			else
				t = -1;
		}
	}
	if (x1 != 0 && y1 != 0) {  // check if hit the pole
		k1 = x1 / y1;
		k2 = (x1*y0 - x0*y1) / y1;
		k3 = k2 + x3;

		k4 = pow(k1, 2) + 1;
		k5 = 2 * k1*k3 + 2 * y3;
		k6 = pow(k3, 2) + pow(y3, 2) - pow(radius, 2);

		delta = pow(k5, 2) - 4 * k4 * k6;
		//std::cout << "hit pole?  delta:" << delta << "\n";
		if (delta >= 0) {
			y = (k5 + sqrt(delta)) / (2 * k4);
			t1 = (y - y0) / y1;
			y = (k5 - sqrt(delta)) / (2 * k4);
			t2 = (y - y0) / y1;
			if (t1 <= t2) {
				y = (k5 + sqrt(delta)) / (2 * k4);
				x = k1 * y - k2;
				t = t1;
				n = Eigen::Vector3d(x - x3, y - y3, 0);
			}
			else {
				x = k1 * y - k2;
				n = Eigen::Vector3d(x - x3, y - y3, 0);
				t = t2;
			}
			z = t * z1 + z0;
			if (z<z3 || z>z4)
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

if (t >= min_t) {
	n=n /sqrt(n.dot(n));
	//std::cout << "hit:" << n << " t:" << t << "\n";
	return true;
}
return false;
 ////////////////////////////////////////////////////////////////////////////
}
