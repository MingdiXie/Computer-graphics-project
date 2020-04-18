#include "Box.h"
#include "Ray.h"
#include <iostream>
#include <vector>
// reference https://github.com/327926791/csc418project/blob/master/src/Box.cpp
double min(double a, double b) {
	return a < b ? a : b;
}

double max(double a, double b) {
	return a > b ? a : b;
}

bool Box::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
		double x_min, y_min, z_min, x_max, y_max, z_max, xd, yd, zd, xe, ye, ze;
		double txmin, txmax, tymin, tymax, tzmin, tzmax;
		std::vector<Eigen::Vector3d> normal;
		int n_id, normal_x, normal_y, normal_z;
		//std::cout << "........ray hit box............"<<lb<<"  "<<rt<<"\n";

		normal.push_back(Eigen::Vector3d(-1,0,0));
		normal.push_back(Eigen::Vector3d(1, 0, 0));
		normal.push_back(Eigen::Vector3d(0, -1, 0));
		normal.push_back(Eigen::Vector3d(0, 1, 0));
		normal.push_back(Eigen::Vector3d(0, 0, -1));
		normal.push_back(Eigen::Vector3d(0, 0, 1));


		t = -1;
		x_min = lb(0);
		y_min = lb(1);
		z_min = lb(2);
		x_max = rt(0);
		y_max = rt(1);
		z_max = rt(2);

		xd = ray.direction(0);
		yd = ray.direction(1);
		zd = ray.direction(2);

		xe = ray.origin(0);
		ye = ray.origin(1);
		ze = ray.origin(2);

		//std::cout << "ray:" << ray.direction << " ray org: " << ray.origin << "\n";

		if (xd>0) {
			txmin = (x_min - xe) / xd;
			txmax = (x_max - xe) / xd;
			normal_x = 0;
		}
		else if (xd < 0) {
			txmin = (x_max - xe) / xd;
			txmax = (x_min - xe) / xd;
			normal_x = 1;
		}
		else {
			txmin = 0;
			txmax = 0;
		}

		if (yd>0) {
			tymin = (y_min - ye) / yd;
			tymax = (y_max - ye) / yd;
			normal_y = 2 ;
		}
		else if (yd < 0){
			tymin = (y_max - ye) / yd;
			tymax = (y_min - ye) / yd;
			normal_y = 3;
		}
		else {
			tymin = tymax = 0;
		}

		if (zd>0) {
			tzmin = (z_min - ze) / zd;
			tzmax = (z_max - ze) / zd;
			normal_z = 4;
		}
		else if (zd < 0) {
			tzmin = (z_max - ze) / zd;
			tzmax = (z_min - ze) / zd;
			normal_z = 5;
		}
		else {
			tzmin = tzmax = 0;
		}

		double tmin, tmax;
		if (txmin > tymin) {
			tmin = txmin;
			n_id = normal_x;
		}
		else if (txmin == tymin) {
			tmin = txmin;
			n_id = 6;
		}
		else{
			tmin = tymin;
			n_id = normal_y;
		}

		if (tmin < tzmin) {
			tmin = tzmin;
			n_id = normal_z;
		}
		else if (tmin == tzmin)
			n_id = 7;

		//tmin = max(max(txmin, tymin), tzmin);
		tmax = min(min(txmax, tymax), tzmax);

		if (tmin > tmax || tmax < 0 || tmin < min_t)
			return false;
		else  {
			t = tmin;
			if (n_id == 6) {
				std::cout << "this is edge\n";
				n = normal[normal_x] + normal[normal_y];
			}
			else if (n_id == 7) {
				std::cout << "this is corner\n";
				n = normal[normal_x] + normal[normal_y] + normal[normal_z];
			}
			else 
			    n = normal[n_id];
			n.normalize();
			//std::cout << "hit " << n << " by " << t <<" min_t:"<<min_t<<"\n";
			//std::cout << "xmin " << txmin<<" "<<x_min<<" "<<xe<<" "<<y_min<<" "<<ye <<" "<<xd<<" "<<yd<< " ymin " << tymin << " zmin:" << tzmin << "\n";
			return true;
		}
  ////////////////////////////////////////////////////////////////////////////
}