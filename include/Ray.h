#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
    public:
        Ray(Vec3 origin, Vec3 direction);
        Vec3 get_point_at(double t) const;

        Vec3 origin;
        Vec3 direction;
};

inline Ray::Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {
}

inline Vec3 Ray::get_point_at(double t) const {
    Vec3 tmp = origin + direction*t;
    return tmp;
}

#endif
