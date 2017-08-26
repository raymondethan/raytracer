#ifndef SPHERE_H
#define SPHERE_H

#include <stdlib.h>
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include "HitRecord.h"
#include "BoundingBox.h"

class Sphere {
    public:
        Sphere(Vec3 center, double radius, std::shared_ptr<Material> matrl_ptr);
        ~Sphere();
        bool intersect_point(const Vec3 &p) const;
        bool hit_bounding_box(const Ray& ray) const;
        bool hit(
            const Ray &r,
            double t_min,
            double t_max,
            HitRecord &record
        ) const;
        static Vec3 random_unit_in_sphere(double radius);
    private:
        Vec3 center;
        double radius;
        std::shared_ptr<Material> matrl_ptr;
        BoundingBox box;
};

inline Sphere::Sphere(Vec3 center, double radius, std::shared_ptr<Material> matrl_ptr) :
    center(center),
	radius(radius),
	matrl_ptr(matrl_ptr),
    box(center, radius) {}

inline Sphere::~Sphere() {}

inline bool Sphere::intersect_point(const Vec3 &p) const{
    return (p-center).norm() == radius;
}

inline bool Sphere::hit_bounding_box(const Ray& ray) const {
    return box.intersect(ray);
}

inline bool Sphere::hit(
    const Ray &r,
    double t_min,
    double t_max,
    HitRecord &record
    ) const {

    record.matrl_ptr = this->matrl_ptr;
    Vec3 oc = r.origin - this->center;
    double a = r.direction.dot(r.direction);
    double b = 2.0*(oc.dot(r.direction));
    double c = oc.dot(oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant <= 0) { return false; }
    double tmp = (-b - sqrt(discriminant)) / (2.0*a);
    if (tmp < t_max && tmp > t_min) {
        record.t = tmp;
        record.p = r.get_point_at(record.t);
        record.normal = (record.p - center) / radius;
        return true;
    }
    tmp = (-b + sqrt(discriminant)) / (2.0*a);
    if (tmp < t_max && tmp > t_min) {
        record.t = tmp;
        record.p = r.get_point_at(record.t);
        record.normal = (record.p - center) / radius;
        return true;
    }
    return false;
}

inline Vec3 Sphere::random_unit_in_sphere(double radius) {
    Vec3 p;
    do {
        p = Vec3(drand48(), drand48(), drand48())*2 - Vec3(1,1,1);
    } while (pow(p.norm(),2) >= radius);
    return p;
}

#endif
