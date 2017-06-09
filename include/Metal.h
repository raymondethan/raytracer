#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {
    public:
        Metal(const Vec3&, double fuzz);
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const;

        Vec3 albedo;
        double fuzz;
};
#endif
