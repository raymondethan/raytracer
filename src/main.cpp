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
    // will DBL_MAX work with the -Ofast compiler flag?
    if (world->hit(r, 0.001, DBL_MAX, rec)) {
        rec.bias_shadow();
        Ray scattered(Vec3(0,0,0),Vec3(0,0,0));
        Vec3 attenuation;

        if (depth < 10 && rec.matrl_ptr->scatter(r, rec, attenuation, scattered)) {
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

        triangle = Triangle(
            Vec3(0,0,-1),
            Vec3(2,0,-1),
            Vec3(0,2,-1),
            std::make_shared<Lambertian>(Vec3(.8,.3,.3))
        );

        // test hitting triange edge
        Ray ray = Ray(Vec3(0,0,0), Vec3(0,0,-4));
        HitRecord rec;
        assert(triangle.hit(ray, .0001, DBL_MAX, rec));
        Vec3 reflection(0,0,4);
        assert(rec.normal.equals(reflection));

        // test hitting triangle interior
        ray = Ray(Vec3(.5,.5,0), Vec3(0,0,-4));
        assert(triangle.hit(ray, .0001, DBL_MAX, rec));
        reflection = Vec3(0,0,4);
        assert(rec.normal.equals(reflection));

        ray = Ray(Vec3(0,0,0), Vec3(.1,.1,-4));
        assert(triangle.hit(ray, .0001, DBL_MAX, rec));
        reflection = Vec3(.1,.1,4);
        assert(rec.normal.equals(reflection));

        // test missing triangle
        ray = Ray(Vec3(0,0,0), Vec3(4,4,-1));
        assert(!triangle.hit(ray, .0001, DBL_MAX, rec));

        // test parallel ray
        ray = Ray(Vec3(0,0,0), Vec3(4,0,0));
        assert(!triangle.hit(ray, .0001, DBL_MAX, rec));

        std::cout << "Triangle passes tests" << std::endl;
        
        return 0;
    }

    std::ofstream file;
    file.open("img.ppm");
    int width = 300;
    int height = 150;
    int ns = 25;
    file << "P3\n" << width << " " << height << "\n255\n";
    Vec3 lower_left(-4,-2,-2);
    Vec3 horizontal(8,0,0);
    Vec3 vertical(0,4,0);
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
    int num_items = 25;
    std::vector<Hitable> list;
    std::vector<std::shared_ptr<Material>> materials;
    size_t num_materials = 5;
    std::shared_ptr<Material> ground = std::make_shared<Lambertian>(Vec3(.8,.3,.3));
    materials.push_back(std::make_shared<Lambertian>(Vec3(.8,.8,0)));
    materials.push_back(std::make_shared<Metal>(Vec3(.8,.6,.2),.3));
    materials.push_back(std::make_shared<Dielectric>(1.5));
    materials.push_back(std::make_shared<Dielectric>(1.5));
    materials.push_back(std::make_shared<Metal>(Vec3(.3,.6,.7),.5));
    list.push_back(Hitable(Sphere(Vec3(0,-100.5,-1), 100, ground)));
    list.push_back(Hitable(Sphere(Vec3(0,0,-1), .5, materials[0])));
    list.push_back(Hitable(Sphere(Vec3(1,0,-1), .5, materials[1])));
    list.push_back(Hitable(Sphere(Vec3(-1,0,-1), .5, materials[2])));
    list.push_back(Hitable(Sphere(Vec3(-1,0,-1), -.45, materials[3])));
    list.push_back(Hitable(Sphere(Vec3(2,0,-2), .7, materials[4])));
    list.push_back(Hitable(Triangle(
        Vec3(-3.5,-1,-1),
        Vec3(-1.5,-1,-1),
        Vec3(-2.5,1,-1),
        materials[4]
    )));
    list.push_back(Hitable(Triangle(
        Vec3(-2.5,1,-1),
        Vec3(-1.5,-1,-1),
        Vec3(-.9,.7,-1.1),
        materials[4] 
    )));
    std::srand(1);
    for (size_t i = 8; i < num_items; ++i) {
        double matrl_num = rand() % num_materials;
        double x = (rand() % 5 - 2) - (double)rand() / RAND_MAX;
        double y = (rand() % 3 - 1) - (double)rand() / RAND_MAX;
        double z = (rand() % 2 - 2) - (double)rand() / RAND_MAX;
        double radius = std::min(((double)rand() / RAND_MAX) + .03, .3);
        //std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", radius: " << radius << std::endl;
        list.push_back(Hitable(Sphere(Vec3(x,y,z), radius, materials[matrl_num])));
    }
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
