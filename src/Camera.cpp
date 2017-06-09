#include <math.h>
#include "Camera.h"

Camera::Camera(
    Vec3 look_from,
	Vec3 look_at,
	Vec3 view_up,
	double vfov,
	double aspect) {

    Vec3 u, v, w;
    double theta = vfov * M_PI/180;
    double half_height = tan(theta/2);
    double half_width = aspect * half_height;
    origin = look_from;
    w = (look_from - look_at).unit_vec();
    u = view_up.cross(w).unit_vec();
    v = w.cross(u);
    lower_left_corner = origin - u*half_width - v*half_height - w;
    horizontal = u*2*half_width;
    vertical = v*2*half_height;
}

Ray Camera::get_ray(double u, double v) {
    Vec3 direction = lower_left_corner + horizontal*u + vertical*v - origin;
    return Ray(origin, direction);
}

Vec3 Camera::random_unit_disc() {
    Vec3 p;
    Vec3 sub(1,1,0);
    do {
        p = Vec3(drand48(), drand48(), 0)*2 - sub;
    } while (p.dot(p) >= 1);
    return p;
}
