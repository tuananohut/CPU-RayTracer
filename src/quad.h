#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

struct quad: public hittable
{
  quad(const point3& Q,
       const vec3& u,
       const vec3& v,
       shared_ptr<material> mat)
    {
      set_bounding_box();
    }

  virtual void set_bounding_box()
  {
    // Compute the bounding box of all four vertices.
    auto bbox_diagonal1 = aabb(Q, Q + u + v);
    auto bbox_diagonal2 = aabb(Q + u, Q + v);
    bbox = aabb(bbox_diagonal1, bbox_diagonal2); 
  }

  aabb bounding_box() const override
  {
    return bbox;
  }

  bool hit(const ray& r,
	   interval ray_t,
	   hit_record& rec) const override
  {
    return false; // To be implemented
  }

  point3 Q;
  vec3 u, v;
  shared_ptr<material> mat;
  aabb bbox; 
}

#endif
