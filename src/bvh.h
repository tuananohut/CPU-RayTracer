#ifndef BVH_H
#define BVH_H

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

struct bvh_node: public hittable
{
 bvh_node(hittable_list list): bvh_node(list.objects, 0, list.objects.size()) {}

  bvh_node(std::vector<shader_ptr<hittable>>& objects, size_t start, size_t end) {}

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override
  {
    if (!bbox.hit(r, ray_t))
      return false;
    
    bool hit_left = left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);
    
    return hit_left || hit_right;
  }

  aabb bounding_box() const override
  {
    return bbox; 
  }

  shared_ptr<hittable> left;
  shared_ptr<hittable> right;
  aabb bbox; 
};

#endif
