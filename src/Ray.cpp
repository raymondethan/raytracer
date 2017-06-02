
#include "Ray.h"
#include <iostream>


Ray::Ray(Vec3 &origin, Vec3 &direction) : origin(origin), direction(direction) {
}

Vec3 Ray::get_point_at(double t) {
    Vec3 tmp;
    tmp = direction*t;
    std::cerr << "no seg fault in get_point_at" << std::endl;
    return tmp;
}
