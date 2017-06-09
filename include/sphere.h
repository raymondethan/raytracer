#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#include "hitable.h"
#include "Material.h"

class Sphere : public Hitable {
    public:
        Sphere(Vec3 center, double radius, Material *matrl_ptr);
        bool intersect_point(const Vec3 &p) const;
        bool hit(
            const Ray &r,
            double t_min,
            double t_max,
            HitRecord &record
        ) const;
        static Vec3 random_unit_in_sphere(double radius);
    private:
        Vec3 center;
        double radius;
        Material *matrl_ptr;
};

#endif
