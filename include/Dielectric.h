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

inline Dielectric::Dielectric(double ri): ref_idx(ri) {}

inline bool Dielectric::scatter(
    const Ray& r_in,
	const HitRecord& rec,
	Vec3& attenuation,
	Ray& scattered) const {

    Vec3 outward_normal;
    Vec3 reflected = Vec3::reflect(r_in.direction, rec.normal);
    double ni_over_nt;
    attenuation = Vec3(1,1,1);
    Vec3 refracted;
    double reflect_prob;
    double cosine;
    if (r_in.direction.dot(rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx + r_in.direction.dot(rec.normal) / r_in.direction.length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1 / ref_idx;
        cosine = -r_in.direction.dot(rec.normal) / r_in.direction.length();
    }
    if (Vec3::refract(r_in.direction, outward_normal, ni_over_nt, refracted)) {
        reflect_prob = this->schlick(cosine, ref_idx);
    } else {
        scattered = Ray(rec.p, reflected);
        reflect_prob = 1;
    }
    if (drand48() < reflect_prob) {
        scattered = Ray(rec.p, reflected);
    } else {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}

inline double Dielectric::schlick(double cosine, double ref_idx) const {
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow(1-cosine,5);
}

#endif
