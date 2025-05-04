#ifndef HITTABLE_H
#define HITTABLE_H

#include "aabb.h"

struct material;

struct hit_record
{
  point3 p;
  vec3 normal;
  shared_ptr<material> mat; 
  double t;
  double u;
  double v; 
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outward_normal)
  {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal; 
  }
};

struct hittable
{
  virtual ~hittable() = default;

  virtual bool hit(const ray& r,
		   interval ray_t,
		   hit_record& rec)
    const = 0;

  virtual aabb bounding_box() const = 0;
};

struct translate: public hittable
{
 translate(shared_ptr<hittable> object, const vec3& offset):
  object(object), offset(offset)
    {
      bbox = object->bounding_box() + offset; 
    }
  
  bool hit(const ray& r,
	   interval ray_t,
	   hit_record& rec) const override
  {
    // Move the ray backwards by the offset
    ray offset_r(r.origin() - offset, r.direction(), r.time());

    // Determine whether an intersection exists along the offset ray (and if so, where)
    if (!object->hit(offset_r, ray_t, rec))
      return false;

    // Move the intersection point forwards by the offset
    rec.p += offset;

    return true; 
  }

  aabb bounding_box() const override { return bbox; }

  shared_ptr<hittable> object;
  vec3 offset;
  aabb bbox; 
};

#endif
