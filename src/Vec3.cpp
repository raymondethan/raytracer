#include <math.h>
#include <iostream>

#include "Vec3.h"

Vec3::Vec3() {}

Vec3::Vec3(double x, double y, double z) {
    this->vec[0] = x;
    this->vec[1] = y;
    this->vec[2] = z;
}

Vec3::Vec3(const double data[]) : Vec3(data[0],data[1],data[2]) {}

bool Vec3::equals(Vec3& other) {
    return (vec == other.getVec());
}

double Vec3::distanceFrom(Vec3 *other) {
    return sqrt(
        pow((this->getX() - other->getX()),2) +
        pow((this->getY() - other->getY()),2) +
        pow((this->getZ() - other->getZ()),2)
    );
}

double Vec3::getX() {
    return this->vec[0];
}

double Vec3::getY() {
    return this->vec[1];
}

double Vec3::getZ() {
    return this->vec[2];
}
        
double Vec3::getR() { return this->getX(); }
double Vec3::getG() { return this->getY(); }
double Vec3::getB() { return this->getZ(); }

double* Vec3::getVec() {
    return vec;
}

Vec3 Vec3::operator+() const { return Vec3(this->vec); }
Vec3 Vec3::operator-() const { return Vec3(-vec[0], -vec[1], -vec[2]); }
Vec3 Vec3::operator+(const Vec3 &rhs) const {
    double new_vec[3];
    for (size_t i = 0; i < size; ++i) {
        new_vec[i] = this->operator[](i) + rhs[i];
    }
    Vec3 tmp(new_vec);
    return tmp;
}
Vec3 Vec3::operator-(const Vec3 &rhs) const {
    Vec3 tmp = -rhs;
    return this->operator+(tmp);
}
 
Vec3 Vec3::operator*(const Vec3 &rhs) const {
    double new_vec[3];
    for (size_t i = 0; i < size; ++i) {
        new_vec[i] = this->operator[](i) * rhs[i];
    }
    Vec3 tmp(new_vec);
    return tmp;
}

double Vec3::operator[](std::size_t i) const {
    if (i >= this->size) {
        throw std::out_of_range("Index out of range of array");
    }
    return this->vec[i];
}
Vec3 Vec3::operator+=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] += rhs[i];
    }
    return *this;
}
Vec3 Vec3::operator-=(const Vec3 &rhs) {
    return this->operator+=(-rhs);
}
Vec3 Vec3::operator*=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] *= rhs[i];
    }
    return *this;
}
Vec3 Vec3::operator/=(const Vec3 &rhs) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] /= rhs[i];
    }
    return *this;
}
Vec3 Vec3::operator+=(double t) {
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] += t;
    }
    return *this;
}
Vec3 Vec3::operator-=(double t) {
    return this->operator+=(-t);
}

Vec3 Vec3::operator*(double t) const {
    double new_vec[3];
    for (std::size_t i = 0; i < size; ++i) {
        new_vec[i] = vec[i]*t;
    }
    Vec3 tmp(new_vec);
    return tmp;
}

Vec3 Vec3::operator/(double t) const {
    return this->operator*(1.0/t);
}

Vec3 Vec3::unit_vec() const {
    return *this / this->norm();
}

double Vec3::dot(const Vec3 &rhs) const {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += vec[i] * rhs[i];
    }
    return sum;
}

Vec3 Vec3::cross(const Vec3 &rhs) const {
    return Vec3(
        vec[1]*rhs[2] - vec[2]*rhs[1],
        vec[2]*rhs[0] - vec[0]*rhs[2],
        vec[0]*rhs[1] - vec[1]*rhs[0]
    );
}

std::size_t Vec3::length() const {
    return size;
}

double Vec3::norm() const {
    return sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));
}

std::string Vec3::to_string() const {
    std::string result = "";
    for (size_t i = 0; i < size-1; ++i) {
        result += std::to_string(vec[i]);
        result += " ";
    }
    result += std::to_string(vec[size-1]);
    return result;
}

Vec3 Vec3::reflect(const Vec3 &v, const Vec3 &n) {
    return v - n*v.dot(n)*2;
}

bool Vec3::refract(
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
