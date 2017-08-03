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
