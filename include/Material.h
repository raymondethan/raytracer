#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "HitRecord.h"

class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const = 0;
};
#endif
