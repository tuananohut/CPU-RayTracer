#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

struct triangle: public hittable
{
 triangle(const vec3& a, const vec3& b, const vec3& c) :
  vertexA(a), vertexB(b), vertexC(c) {}

  bool hit(const ray& r,
	   double ray_tmin,
	   double ray_tmax,
	   hit_record& rec)
    const override
  {
    point3 a = this->vertexA;
    point3 b = this->vertexB;
    point3 c = this->vertexC;

    vec3 E1 = b - a;
    vec3 E2 = c - a;

    vec3 h = cross(r.direction(), E2);
    double det = dot(E1, h);
    if (fabs(det) < 1e-8)
      return false;

    double invDet = 1.0 / det;

    vec3 s = r.origin() - a;
    double u = dot(s, h) * invDet;
    if (u < 0 || u > 1)
      return false;

    vec3 q = cross(s, E1);
    double v = dot(r.direction(), q) * invDet;
    if (v < 0 || u + v > 1)
      return false;

    double t = dot(E2, q) * invDet;
    if (t < ray_tmin || t > ray_tmax)
      return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.normal = unit_vector(cross(E1, E2));

    return true;
  }

point3 vertexA;
point3 vertexB;
point3 vertexC;
};


#endif
