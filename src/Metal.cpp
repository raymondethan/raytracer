#include "Metal.h"
#include "Sphere.h"

Metal::Metal(const Vec3 &vec, double f) : albedo(vec) {
    if (f < 1) { this->fuzz = f; }
    else { this->fuzz = 1; }
}

bool Metal::scatter(
    const Ray& r_in,
    const HitRecord& rec,
	Vec3& attenuation,
	Ray& scattered) const {

    Vec3 reflected = Vec3::reflect(r_in.direction.unit_vec(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (scattered.direction.dot(rec.normal) > 0);
}
