#include <math.h>
#include <stdlib.h>
#include "Camera.h"

Camera::Camera(
    Vec3 &look_from,
	Vec3 &look_at,
	Vec3 &view_up,
	double vfov,
	double aspect,
    double aperture,
    double focus_dist)
    {

    lens_radius = aperture / 2; 
    double theta = vfov * M_PI/180;
    double half_height = tan(theta/2);
    double half_width = aspect * half_height;
    origin = look_from;
    w = (look_from - look_at).unit_vec();
    u = view_up.cross(w).unit_vec();
    v = w.cross(u);
    lower_left_corner = origin - (u*half_width + v*half_height + w)*focus_dist;
    horizontal = u*2*half_width*focus_dist;
    vertical = v*2*half_height*focus_dist;
}

Ray Camera::get_ray(double s, double t) {
    Vec3 rd = random_in_unit_disc() * lens_radius;
    Vec3 offset = u * rd.getX() + v * rd.getY();
    Vec3 direction = lower_left_corner + horizontal*s + vertical*t - origin - offset;
    return Ray(origin + offset, direction);
}

Vec3 Camera::random_in_unit_disc() {
    Vec3 p;
    //Vec3 sub(1,1,0);
    do {
        p = Vec3(drand48(), drand48(), 0)*2 - Vec3(1,1,0);
    } while (p.dot(p) >= 1);
    return p;
}
