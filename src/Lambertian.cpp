#include "Lambertian.h"
#include "Sphere.h"

Lambertian::Lambertian(const Vec3 &vec) : albedo(vec) {}

bool Lambertian::scatter(
    const Ray& r_in,
	const HitRecord& rec,
	Vec3& attenuation,
	Ray& scattered) const {

    Vec3 target = rec.p + rec.normal + Sphere::random_unit_in_sphere(1);
    scattered = Ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
}
