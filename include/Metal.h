#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {
    public:
        Metal(const Vec3&, double fuzz);
        ~Metal() = default;
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const;

        Vec3 albedo;
        double fuzz;
};

inline Metal::Metal(const Vec3 &vec, double f) : albedo(vec) {
    if (f < 1) { this->fuzz = f; }
    else { this->fuzz = 1; }
}

inline bool Metal::scatter(
    const Ray& r_in,
    const HitRecord& rec,
	Vec3& attenuation,
	Ray& scattered) const {

    Vec3 reflected = Vec3::reflect(r_in.direction.unit_vec(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (scattered.direction.dot(rec.normal) > 0);
}

#endif
