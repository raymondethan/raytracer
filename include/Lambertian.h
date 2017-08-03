#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"
#include "Sphere.h"

class Lambertian : public Material {
    public:
        Lambertian(const Vec3 &vec);
        virtual bool scatter(const Ray&, const HitRecord&, Vec3&, Ray&) const;

        Vec3 albedo;
};

inline Lambertian::Lambertian(const Vec3 &vec) : albedo(vec) {}

inline bool Lambertian::scatter(
    const Ray& r_in,
	const HitRecord& rec,
	Vec3& attenuation,
	Ray& scattered) const {

    Vec3 target = rec.p + rec.normal + Sphere::random_unit_in_sphere(1);
    scattered = Ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
}

#endif
