#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
    public:
        Ray(Vec3 origin, Vec3 direction);
        Vec3 get_point_at(double t) const;

        Vec3 origin;
        Vec3 direction;
        Vec3 inv_dir;
        size_t sign_x, sign_y, sign_z;
};

inline Ray::Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {
    inv_dir = direction.inverse();
    sign_x = inv_dir.getX() < 0 ? 1 : 0;
    sign_y = inv_dir.getY() < 0 ? 1 : 0;
    sign_z = inv_dir.getZ() < 0 ? 1 : 0;
}

inline Vec3 Ray::get_point_at(double t) const {
    Vec3 tmp = origin + direction*t;
    return tmp;
}

#endif
