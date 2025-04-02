#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record
{
  point3 p;
  vec3 normal;
  double t;
};

struct hittable
{
  virtual ~hittable() = default;

  virtual bool hit(const ray& r,
		   double ray_tmin,
		   double ray_tmax,
		   hit_record& rec) const = 0;
};

#endif
