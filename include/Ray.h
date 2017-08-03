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

#endif
