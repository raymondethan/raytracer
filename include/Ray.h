#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
    public:
        Ray(Vec3 origin, Vec3 direction);
        void get_point_at(double t, Vec3 &ret_pt) const;

        Vec3 origin;
        Vec3 direction;
};

#endif
