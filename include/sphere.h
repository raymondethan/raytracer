#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"

class Sphere {
    public:
        Sphere(Vec3 center, int radius);
        bool intersect(Vec3 *p);
    private:
        Vec3 center;
        int radius;
};

#endif
