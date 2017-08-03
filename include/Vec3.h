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
        Vec3(const double data[]);
        bool equals(Vec3& vec2);
        
        double distanceFrom(Vec3 *other);
        double getX();
        double getY();
        double getZ();
    
        double getR();
        double getG();
        double getB();

        double* getVec();

        Vec3 operator+() const;
        Vec3 operator-() const;
        Vec3 operator+(const Vec3 &rhs) const;
        Vec3 operator-(const Vec3 &rhs) const;
        Vec3 operator*(const Vec3 &rhs) const;
        double operator[](std::size_t i) const;
        Vec3 operator+=(const Vec3 &rhs);
        Vec3 operator-=(const Vec3 &rhs);
        Vec3 operator*=(const Vec3 &rhs);
        Vec3 operator/=(const Vec3 &rhs);
        Vec3 operator+=(double t);
        Vec3 operator-=(double t);
        Vec3 operator*(double t) const;
        Vec3 operator/(double t) const;
        Vec3 unit_vec() const;

        std::size_t length() const;
        double dot(const Vec3 &rhs) const;
        Vec3 cross(const Vec3 &rhs) const;
        double norm() const;
        static Vec3 reflect(const Vec3 &v, const Vec3 &n);
        static bool refract(
            const Vec3 &v,
        	const Vec3 &n,
        	double ni_over_nt,
        	Vec3 &refracted
        );
        std::string to_string() const;
        
    private:
        double vec[3];
        std::size_t size = 3;
};

#endif
