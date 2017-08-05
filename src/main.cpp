#include <stdio.h>
#include <memory>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <float.h>
#include <math.h>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "HitableList.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

Vec3 color(const Ray& r, HitableList *world, int depth) {
    HitRecord rec;
    if (world->hit(r, 0.001, DBL_MAX, rec)) {
        Ray scattered(Vec3(0,0,0),Vec3(0,0,0));
        Vec3 attenuation;

        if (depth < 50 && rec.matrl_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
         }
        return Vec3(0,0,0);
    }
    Vec3 dir = r.direction.unit_vec();
    double t = .5*(dir.getY() + 1.0);
    return Vec3(1, 1, 1)*(1.0-t) + Vec3(.5, .7, 1)*t;
}

int main(int argc, const char * argv[]) {
    std::cout << "Program start" << std::endl;
    if (argc > 1 && (std::string(argv[1])).compare("tests") == 0) {

        Vec3 p(1,1,1);
        Vec3 p2(1,1,2);
        Vec3 p3(p2);
        assert(&p3 != &p2);

        double dist;
        dist = p.distanceFrom(&p2);
        assert(dist == 1);
        
        dist = p2.distanceFrom(&p);
        assert(dist == 1);
        
        dist = p.distanceFrom(&p);
        assert(dist == 0);

        assert(p.getX() == 1 && p.getR() == 1);
        assert(p.getG() == 1 && p.getY() == 1);
        assert(p.getB() == 1 && p.getZ() == 1);

        assert(p2[2] == 2);
        try {
            p2[-1];
            std::cout << "bounds checking failed" << std::endl;
            return 1;
        } catch(const std::out_of_range& e) {
        }
        
        try {
            p2[3];
            std::cout << "bounds checking failed" << std::endl;
            return 1;
        } catch(const std::out_of_range& e) {
        }
        p3 = -p;
        assert(p3.getX() == -1 && p3.getY() == -1 && p3.getZ() == -1);
        p3 *= p2;
        assert(p3.getX() == -1 && p3.getY() == -1 && p3.getZ() == -2);
        p2 += -p;
        assert(p2.getX() == 0 && p2.getY() == 0 && p2.getZ() == 1);
        
        assert(p.to_string().compare("1.000000 1.000000 1.000000") == 0);

        Vec3 p4(2,2,2);
        p4 = p4/2;
        assert(p4.getX() == 1 && p4.getY() == 1 && p4.getZ() == 1);

        double dot = p3.dot(p2);
        assert(dot == -2);

        p3 = Vec3(2,0,1);
        p2 = Vec3(1,2,1);
        p = p3.cross(p2);
        assert(p.getX() == -2 && p.getY() == -1 && p.getZ() == 4);
        
        p3 = p3.unit_vec();
        assert(p3.norm() < 1.01 && p3.norm() > .999);
        
        std::cout << "Vec3 passes tests" << std::endl;

        Vec3 origin(0,0,0);
        Vec3 direction(1,1,1);
        Ray r1(origin, direction);
        Vec3 pt = r1.get_point_at(1);
        Vec3 answer = Vec3(1,1,1);
        assert(pt.equals(answer));
        
        std::cout << "Ray passes tests" << std::endl;

        Vec3 center(0,0,0);
        Sphere sphere(center, 1, std::make_shared<Lambertian>(Vec3(.8,.3,.3)));
        p = Vec3(0,0,1);
        assert(sphere.intersect_point(p));

        std::cout << "Sphere passes tests" << std::endl;

        // Triange tests
        Triangle triangle = Triangle(
            Vec3(0,0,0),
            Vec3(1,0,0),
            Vec3(0,1,0),
            std::make_shared<Lambertian>(Vec3(.8,.3,.3))
        );

        Vec3 inside = Vec3(.5,.5,0);
        assert(triangle.intersect_point(inside));
        inside = Vec3(0,0,0);
        assert(triangle.intersect_point(inside));

        Vec3 outside = Vec3(.5,.5,.5);
        assert(!triangle.intersect_point(outside));
        outside = Vec3(.5,-.5,0);
        assert(!triangle.intersect_point(outside));

        std::cout << "Triangle passes tests" << std::endl;

        return 0;
    }

    std::ofstream file;
    file.open("img.ppm");
    int width = 400;
    int height = 200;
    int ns = 100;
    file << "P3\n" << width << " " << height << "\n255\n";
    Vec3 lower_left(-2,-1,-1);
    Vec3 horizontal(4,0,0);
    Vec3 vertical(0,2,0);
    Vec3 origin(0,0,0);
    Vec3 look_from(1,2,2);
    Vec3 look_at(0,0,-1);
    Vec3 vew_up(0,1,0);
    double dist_to_focus = (look_from - look_at).norm();
    std::cout << "focus: " << dist_to_focus << std::endl;
    double aperture = 2;
    Camera camera(
        look_from,
        look_at,
        vew_up,
		40,
		double(width)/double(height),
        aperture,
        dist_to_focus
    );
    int num_items = 6;
    std::vector<Hitable> list;
    std::shared_ptr<Material> sphere0_matrl = std::make_shared<Lambertian>(Vec3(.8,.3,.3));
    list.push_back(Hitable(Sphere(Vec3(0,0,-1), .5, sphere0_matrl)));
    std::shared_ptr<Material> sphere1_matrl = std::make_shared<Lambertian>(Vec3(.8,.8,0));
    list.push_back(Hitable(Sphere(Vec3(0,-100.5,-1), 100, sphere1_matrl)));
    std::shared_ptr<Material> sphere2_matrl = std::make_shared<Metal>(Vec3(.8,.6,.2),.3);
    list.push_back(Hitable(Sphere(Vec3(1,0,-1), .5, sphere2_matrl)));
    std::shared_ptr<Material> sphere3_matrl = std::make_shared<Dielectric>(1.5);
    list.push_back(Hitable(Sphere(Vec3(-1,0,-1), .5, sphere3_matrl)));
    std::shared_ptr<Material> sphere4_matrl = std::make_shared<Dielectric>(1.5);
    list.push_back(Hitable(Sphere(Vec3(-1,0,-1), -.45, sphere4_matrl)));
    std::shared_ptr<Material> sphere5_matrl = std::make_shared<Metal>(Vec3(.3,.6,.7),.5);
    list.push_back(Hitable(Sphere(Vec3(2,0,-2), .7, sphere5_matrl)));
    HitableList *world = new HitableList(list, num_items);
    for (int j = height; j>= 0; --j) {
        for (int i = 0; i < width; ++i) {
            Vec3 rgb(0,0,0);
            for (size_t n = 0; n < ns; ++n) {
                double u = double(i + drand48()) / double(width);
                double v = double(j + drand48()) / double(height);
                Ray r = camera.get_ray(u, v);
                Vec3 vec = color(r, world, 0);
                rgb += vec;

            }
            rgb = rgb / ns;
            int ir = (255.99*sqrt(rgb.getR()));
            int ig = (255.99*sqrt(rgb.getG()));
            int ib = (255.99*sqrt(rgb.getB()));
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    delete world;
    world = 0;
    file.close();
    return 0;
}
