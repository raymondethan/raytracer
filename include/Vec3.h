#ifndef POINT_H
#define POINT_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <string>
#include "math.h"

class Vec3 {
    public:
        Vec3();
        Vec3(double x, double y, double z);
        Vec3(const double data[]);
        bool equals(Vec3& vec2);
        
        double distanceFrom(Vec3 *other);
        double getX() const;
        double getY() const;
        double getZ() const;
    
        double getR() const;
        double getG() const;
        double getB() const;

        double* getVec();

        Vec3 operator+() const;
        Vec3 operator-() const;
        Vec3 operator+(const Vec3 &rhs) const;
        Vec3 operator-(const Vec3 &rhs) const;
        Vec3 operator*(const Vec3 &rhs) const;
        double& operator[](std::size_t i);
        const double& operator[](std::size_t i) const;
        Vec3 operator+=(const Vec3 &rhs);
        Vec3 operator-=(const Vec3 &rhs);
        Vec3 operator*=(const Vec3 &rhs);
        Vec3 operator/=(const Vec3 &rhs);
        Vec3 operator+=(double t);
        Vec3 operator-=(double t);
        Vec3 operator*(double t) const;
        Vec3 operator/(double t) const;
        Vec3 inverse() const;
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

inline Vec3::Vec3() {}

inline Vec3::Vec3(double x, double y, double z) {
    this->vec[0] = x;
    this->vec[1] = y;
    this->vec[2] = z;
}

inline Vec3::Vec3(const double data[]) : Vec3(data[0],data[1],data[2]) {}

inline bool Vec3::equals(Vec3& other) {
    for (size_t i = 0; i < size; ++i) {
        if (vec[i] != other[i]) {
            return false;
        }
    }
    return true;
}

inline double Vec3::distanceFrom(Vec3 *other) {
    return sqrt(
        pow((this->getX() - other->getX()),2) +
        pow((this->getY() - other->getY()),2) +
        pow((this->getZ() - other->getZ()),2)
    );
}

inline double Vec3::getX() const {
    return this->vec[0];
}

inline double Vec3::getY() const {
    return this->vec[1];
}

inline double Vec3::getZ() const {
    return this->vec[2];
}
        
inline double Vec3::getR() const { return this->getX(); }
inline double Vec3::getG() const { return this->getY(); }
inline double Vec3::getB() const { return this->getZ(); }

inline double* Vec3::getVec() {
    return vec;
}

inline Vec3 Vec3::operator+() const { return Vec3(this->vec); }
inline Vec3 Vec3::operator-() const { return Vec3(-vec[0], -vec[1], -vec[2]); }
inline Vec3 Vec3::operator+(const Vec3 &rhs) const {
    double new_vec[3];
    for (size_t i = 0; i < size; ++i) {
        new_vec[i] = this->operator[](i) + rhs[i];
    }
    Vec3 tmp(new_vec);
    return tmp;
}
inline Vec3 Vec3::operator-(const Vec3 &rhs) const {
    Vec3 tmp = -rhs;
    return this->operator+(tmp);
}
 
inline Vec3 Vec3::operator*(const Vec3 &rhs) const {
    double new_vec[3];
    for (size_t i = 0; i < size; ++i) {
        new_vec[i] = this->operator[](i) * rhs[i];
    }
    Vec3 tmp(new_vec);
    return tmp;
}

inline double& Vec3::operator[](std::size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range of array");
    }
    return vec[i];
}

inline const double& Vec3::operator[](std::size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range of array");
    }
    return vec[i];
}

inline Vec3 Vec3::operator+=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] += rhs[i];
    }
    return *this;
}
inline Vec3 Vec3::operator-=(const Vec3 &rhs) {
    return this->operator+=(-rhs);
}
inline Vec3 Vec3::operator*=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] *= rhs[i];
    }
    return *this;
}
inline Vec3 Vec3::operator/=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] /= rhs[i];
    }
    return *this;
}
inline Vec3 Vec3::operator+=(double t) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] += t;
    }
    return *this;
}
inline Vec3 Vec3::operator-=(double t) {
    return this->operator+=(-t);
}

inline Vec3 Vec3::operator*(double t) const {
    double new_vec[3];
    for (std::size_t i = 0; i < size; ++i) {
        new_vec[i] = vec[i]*t;
    }
    Vec3 tmp(new_vec);
    return tmp;
}

inline Vec3 Vec3::operator/(double t) const {
    return this->operator*(1.0/t);
}

inline Vec3 Vec3::inverse() const {
    return Vec3((1/vec[0]), (1/vec[1]), (1/vec[2]));
}

inline Vec3 Vec3::unit_vec() const {
    return *this / this->norm();
}

inline double Vec3::dot(const Vec3 &rhs) const {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += vec[i] * rhs[i];
    }
    return sum;
}

inline Vec3 Vec3::cross(const Vec3 &rhs) const {
    return Vec3(
        vec[1]*rhs[2] - vec[2]*rhs[1],
        vec[2]*rhs[0] - vec[0]*rhs[2],
        vec[0]*rhs[1] - vec[1]*rhs[0]
    );
}

inline std::size_t Vec3::length() const {
    return size;
}

inline double Vec3::norm() const {
    return sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));
}

inline std::string Vec3::to_string() const {
    std::string result = "";
    for (size_t i = 0; i < size-1; ++i) {
        result += std::to_string(vec[i]);
        result += " ";
    }
    result += std::to_string(vec[size-1]);
    return result;
}

inline Vec3 Vec3::reflect(const Vec3 &v, const Vec3 &n) {
    return v - n*v.dot(n)*2;
}

inline bool Vec3::refract(
    const Vec3 &v,
	const Vec3 &n,
	double ni_over_nt,
	Vec3 &refracted) {

    Vec3 uv = v.unit_vec();
    double dt = uv.dot(n);
    double discriminant = 1 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = (uv - n*dt)*ni_over_nt - n*sqrt(discriminant);
        return true;
    }
    return false;
}

#endif
