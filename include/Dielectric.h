#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric: public Material {
    public:
        Dielectric(double ri);
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const;

        double ref_idx;
    private:
        double schlick(double cosine, double ref_idx) const;
};

#endif
