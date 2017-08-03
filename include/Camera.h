#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
    public:
        Camera(
            Vec3 &look_from,
        	Vec3 &look_at,
        	Vec3 &view_up,
            double vfov,
            double aspect,
            double aperture,
            double focus_dist
        );
        Ray get_ray(double, double);
        static Vec3 random_in_unit_disc();

        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u, v, w;
        double lens_radius;
};

inline Ray Camera::get_ray(double s, double t) {
    Vec3 rd = random_in_unit_disc() * lens_radius;
    Vec3 offset = u * rd.getX() + v * rd.getY();
    Vec3 direction = lower_left_corner + horizontal*s + vertical*t - origin - offset;
    return Ray(origin + offset, direction);
}

inline Vec3 Camera::random_in_unit_disc() {
    Vec3 p;
    do {
        p = Vec3(drand48(), drand48(), 0)*2 - Vec3(1,1,0);
    } while (p.dot(p) >= 1);
    return p;
}

#endif
