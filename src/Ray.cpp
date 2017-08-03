
#include "Ray.h"
#include <iostream>


Ray::Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {
}

void Ray::get_point_at(double t, Vec3 &ret_pt) const {
    ret_pt = origin + direction*t;
}
