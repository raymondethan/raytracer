#ifndef HITABLELIST
#define HITABLELIST

#include "hitable.h"

class HitableList : public Hitable {
    public:
        HitableList(Hitable **l, int n);
        virtual bool hit(
                const Ray &r,
                double t_min,
                double t_max,
                HitRecord &rec
        ) const;

        Hitable **hitables;
        int size;
};

#endif
