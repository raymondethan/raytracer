#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>

#include "Vec3.h"
#include "Ray.h"

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
        
        std::cout << p.to_string() << std::endl;
        assert(p.to_string().compare("1.000000 1.000000 1.000000") == 0);
        
        std::cout << "Vec3 passes tests" << std::endl;

        Vec3 origin(0,0,0);
        Vec3 direction(1,1,1);
        Ray r1(origin, direction);
        Vec3 pt = r1.get_point_at(1);
        std::cout << pt.to_string() << std::endl;
        Vec3 answer = Vec3(1,1,1);
        assert(pt.equals(answer));
        
        std::cout << "Ray passes tests" << std::endl;
    }

    std::ofstream file;
    file.open("img.ppm");
    int width = 200;
    int height = 100;
    file << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height; j>= 0; --j) {
        for (int i = 0; i < width; ++i) {
            Vec3 vec(float(i) / float(width),float(j) / float(height),.2);
            int ir = (255.99*vec.getR());
            int ig = (255.99*vec.getG());
            int ib = (255.99*vec.getB());
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    file.close();
    return 0;
}
