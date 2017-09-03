#ifndef HIT_RECORD
#define HIT_RECORD

#include <stdlib.h>

class Material;

struct HitRecord {
    double t;
    Vec3 p;
    Vec3 normal;
    std::shared_ptr<Material> matrl_ptr;
    double bias = .0004;

    void bias_shadow() {
        p = p + normal * bias;
    }
};

#endif
