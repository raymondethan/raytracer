#include <math.h>
#include <iostream>

#include "Vec3.h"

Vec3::Vec3() : vec(3), size(3) {}

Vec3::Vec3(double x, double y, double z) : vec(3), size(3) {
    this->vec[0] = x;
    this->vec[1] = y;
    this->vec[2] = z;
}

Vec3::Vec3(std::vector<double> data) : Vec3(data[0],data[1],data[2]) {}

//Vec3& operator=(Vec3 &data) {
//    Vec3 tmp(data.getVec());
//    return tmp;
//}

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

std::vector<double>& Vec3::getVec() {
    return vec;
}

Vec3 Vec3::operator+() const { return Vec3(this->vec); }
Vec3 Vec3::operator-() const { return Vec3(-vec[0], -vec[1], -vec[2]); }
Vec3 Vec3::operator+(const Vec3 &rhs) const {
    std::vector<double> new_vec(3);
    for (size_t i = 0; i < size; ++i) {
        new_vec.push_back(this->operator[](i) + rhs[i]);
    }
    Vec3 tmp(new_vec);
    std::cerr << "operator + for 2 vecs" << std::endl;
    std::cerr << tmp.to_string() << std::endl;
    return tmp;
}
Vec3 Vec3::operator-(const Vec3 &rhs) const {
    Vec3 tmp = -rhs;
    return this->operator+(tmp);
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
    std::vector<double> new_vec(3);
    std::cerr << "* operator with int: " << std::endl;
    for (std::size_t i = 0; i < size; ++i) {
        new_vec.push_back(vec[i]*t);
    }
    Vec3 tmp(new_vec);
    std::cerr << "just created tmp" << std::endl;
    std::cerr << tmp.to_string() << std::endl;
    std::cerr << "just printed tmp" << std::endl;
    return tmp;
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
