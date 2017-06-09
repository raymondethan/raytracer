#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Hitable.h"

class Material {
    public:
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const = 0;
};
#endif
