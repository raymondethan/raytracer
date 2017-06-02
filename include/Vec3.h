#ifndef POINT_H
#define POINT_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <string>

class Vec3 {
    public:
        Vec3();
        Vec3(double x, double y, double z);
        Vec3(std::vector<double> data);
        //Vec3& operator=(Vec3 &data);
        bool equals(Vec3& vec2);
        
        double distanceFrom(Vec3 *other);
        double getX();
        double getY();
        double getZ();
    
        double getR();
        double getG();
        double getB();

        std::vector<double>& getVec();

        Vec3 operator+() const;
        Vec3 operator-() const;
        Vec3 operator+(const Vec3 &rhs) const;
        Vec3 operator-(const Vec3 &rhs) const;
        double operator[](std::size_t i) const;
        Vec3 operator+=(const Vec3 &rhs);
        Vec3 operator-=(const Vec3 &rhs);
        Vec3 operator*=(const Vec3 &rhs);
        Vec3 operator/=(const Vec3 &rhs);
        Vec3 operator+=(double t);
        Vec3 operator-=(double t);
        Vec3 operator*(double t) const;

        std::size_t length() const;
        std::string to_string() const;
        
    private:
        std::vector<double> vec;
        std::size_t size;
};

#endif
