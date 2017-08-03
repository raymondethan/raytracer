
#include "Ray.h"
#include <iostream>


Ray::Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {
}

Vec3 Ray::get_point_at(double t) const {
    Vec3 tmp = origin + direction*t;
    return tmp;
}
