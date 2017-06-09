#ifndef HITABLE
#define HITABLE

#include "Ray.h"

class Material;

struct HitRecord {
    double t;
    Vec3 p;
    Vec3 normal;
    Material *matrl_ptr;
};

class Hitable {
    public:
        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif
