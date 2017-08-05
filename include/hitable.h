#ifndef HITABLE
#define HITABLE

#include <stdlib.h>
#include <variant>
#include <iostream>
#include "Ray.h"
#include "HitRecord.h"
#include "Sphere.h"

class Hitable {
    public:

        Hitable(Sphere sphere) : shape(sphere) {}

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
            return std::visit([&r, t_min, t_max, &rec](auto&& arg) {
                    return arg.hit(r, t_min, t_max, rec);
            }, shape);
        }

        std::variant<Sphere> shape;
};

#endif
