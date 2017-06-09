#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {
    public:
        Lambertian(const Vec3 &vec);
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const;

        Vec3 albedo;
};

#endif
