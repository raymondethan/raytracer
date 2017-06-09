#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
    public:
        Camera(
            Vec3 look_from,
        	Vec3 look_at,
        	Vec3 view_up,
            double vfov,
            double aspect
        );
        Ray get_ray(double, double);
        static Vec3 random_unit_disc();

        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif
