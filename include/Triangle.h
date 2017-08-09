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
			xz(z - x),
			xy(y - x),
			normal(xy.cross(xz)),
			D(normal.dot(x)),
			matrl_ptr(matrl_ptr) {}

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
        Vec3 xz;
        Vec3 xy;
        Vec3 normal;
        // Ax + By + Cz + D = 0 - equation of plane
        double D;
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
    double normalDotDirection =  normal.dot(r.direction);
    // ray and triangle are parallel
    if (abs(normalDotDirection) < t_min) return false;

    double t = (normal.dot(r.direction) + D) / normalDotDirection;
    std::cout << "D: " << D << ", t: " << t << std::endl;
    // triangle is behind ray
    if (t < 0) return false;

    Vec3 point = r.origin + r.direction * t;
    return intersect_point(point);
}

#endif
