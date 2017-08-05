#ifndef HITABLELIST
#define HITABLELIST

#include "Hitable.h"

class HitableList {
    public:
        HitableList(std::vector<Hitable> l, int n);
        virtual bool hit(
                const Ray &r,
                double t_min,
                double t_max,
                HitRecord &rec
        ) const;

        std::vector<Hitable> hitables;
        int size;
};

inline HitableList::HitableList(std::vector<Hitable> l, int n) : hitables(l), size(n) {}

inline bool HitableList::hit(
        const Ray &r,
        double t_min,
        double t_max,
        HitRecord &rec
    ) const {
    
    HitRecord tmp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (size_t i = 0; i < size; ++i) {
        if (hitables[i].hit(r, t_min, closest_so_far, tmp_rec)) {
            hit_anything = true;
            closest_so_far = tmp_rec.t;
            rec = tmp_rec;
        }
    }
    return hit_anything;
}

#endif
