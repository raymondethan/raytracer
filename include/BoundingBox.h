#ifndef BOUNDING_BOX
#define BOUNDING_BOX

struct BoundingBox {
    Vec3 max_point;
    Vec3 min_point;
    Vec3* bounds[2] = {&min_point, &max_point};

    BoundingBox(std::vector<Vec3> indices) {
        extend_box(indices);
    }

    BoundingBox(Vec3& center, double radius) {
        radius = abs(radius);
        min_point = Vec3(center[0]-radius, center[1]-radius, center[2]-radius);
        max_point = Vec3(center[0]+radius, center[1]+radius, center[2]+radius);
    }

    void extend_box(std::vector<Vec3> indices) {
        for (const auto& index: indices) {
            for (size_t i = 0; i < index.length(); ++i) {
                if (index[i] < min_point[i]) {
                    // possible seg fault?
                    min_point[i] = (double)index[i];
                } else if (index[i] > max_point[i]) {
                    max_point[i] = (double)index[i];
                }
            }
        }
    }

    // doesn't work correctly when spheres nested inside each other
    bool intersect(const Ray& ray) const {
        if (isOriginBounded(ray.origin)) {
            //std::cerr << "bounded" << std::endl;
            return true;
        }

        double tmin, tmax, tymin, tymax, tzmin, tzmax;

        tmin = (bounds[ray.sign_x]->getX() - ray.origin.getX()) * ray.inv_dir.getX();
        tmax = (bounds[1-ray.sign_x]->getX() - ray.origin.getX()) * ray.inv_dir.getX();
        tymin = (bounds[ray.sign_y]->getY() - ray.origin.getY()) * ray.inv_dir.getY();
        tymax = (bounds[1-ray.sign_y]->getY() - ray.origin.getY()) * ray.inv_dir.getY();

        if ((tmin > tymax) || (tymin > tmax))
            return false;
        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;

        tzmin = (bounds[ray.sign_z]->getZ() - ray.origin.getZ()) * ray.inv_dir.getZ();
        tzmax = (bounds[1-ray.sign_z]->getZ() - ray.origin.getZ()) * ray.inv_dir.getZ();

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;
        if (tzmin > tmin)
            tmin = tzmin;
        if (tzmax < tmax)
            tmax = tzmax;

        return true;
    }

    bool isOriginBounded(const Vec3& origin) const {
        return (
            origin.getX() >= min_point.getX() &&
            origin.getY() >= min_point.getY() &&
            origin.getZ() >= min_point.getZ() &&
            origin.getX() <= max_point.getX() &&
            origin.getY() <= max_point.getY() &&
            origin.getZ() <= max_point.getZ()
        );
    }
};

#endif
