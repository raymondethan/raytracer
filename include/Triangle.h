#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include "HitRecord.h"

class Triangle {
    public:
        Triangle(
            Vec3 x,
            Vec3 y,
            Vec3 z,
            std::shared_ptr<Material> matrl_ptr
        ) : x(x),
			y(y),
			z(z),
			xy(y - x),
			xz(z - x),
			normal(xy.cross(xz)),
			matrl_ptr(matrl_ptr) {
                normal = normal.unit_vec();
            }

        ~Triangle() {}
        bool intersect_point(const Vec3 &p) const;
        bool hit(
            const Ray &r,
            double t_min,
            double t_max,
            HitRecord &record
        ) const;

    private:
        Vec3 x;
        Vec3 y;
        Vec3 z;
        Vec3 xy;
        Vec3 xz;
        Vec3 normal;
        std::shared_ptr<Material> matrl_ptr;
};

inline bool Triangle::intersect_point(const Vec3 &p) const {
    Vec3 xp = p - x;

    Vec3 xzCrossxp = xz.cross(xp);
    Vec3 xzCrossxy = xz.cross(xy);

    if (xzCrossxp.dot(xzCrossxy) < 0) {
        return false;
    }

    Vec3 xyCrossxp = xy.cross(xp);
    Vec3 xyCrossxz = xy.cross(xz);

    if (xyCrossxp.dot(xyCrossxz) < 0) {
        return false;
    }

    // Compute barycentric coordinates
    double denom = xyCrossxz.norm();
    double u = xzCrossxp.norm() / denom;
    double v = xyCrossxp.norm()/ denom;

    // Check if point is in triangle
    return (u + v <= 1);
}

inline bool Triangle::hit(
    const Ray &r,
    double t_min,
    double t_max,
    HitRecord &record
) const {

    record.matrl_ptr = this->matrl_ptr;
    Vec3 pvec = r.direction.cross(xz);
    double det = xy.dot(pvec);
    if (det < t_min) return false;
    if (abs(det) < t_min) return false;

    double invDet = 1 / det;
    Vec3 tvec = r.origin - x;
    double u = tvec.dot(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vec3 qvec = tvec.cross(xy);
    double v = r.direction.dot(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;

    double t = xz.dot(qvec) * invDet;
    if (t < t_min || t > t_max) return false;

    record.t = t;
    record.p = r.get_point_at(t);
    record.normal = normal;
    return true;
}

#endif
