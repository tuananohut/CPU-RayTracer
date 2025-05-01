#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

#include <cmath>

struct quad: public hittable
{
  quad(const point3& Q,
       const vec3& u,
       const vec3& v,
       shared_ptr<material> mat)
    : Q(Q), u(u), v(v), mat(mat)
    {
      auto n = cross(u, v);
      normal = unit_vector(n);
      D = dot(normal, Q); 
      w = n / dot(n, n); 
      
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
    auto denom = dot(normal, r.direction());

    // No hit if the ray is parallel to the plane.
    if (std::fabs(denom) < 1e-8)
      {
	return false;
      }
      

    // Return false if the hit point parameter t is outside the ray interval.
    auto t = (D - dot(normal, r.origin())) / denom;
    if (!ray_t.contains(t))
      {
	return false;
      }
    
    // Determine if the hit point lies within the planar shape using its plane coordinates.
    auto intersection = r.at(t);
    vec3 planar_hitpt_vector = intersection - Q;
    auto alpha = dot(w, cross(planar_hitpt_vector, v));
    auto beta = dot(w, cross(u, planar_hitpt_vector));

    if (!is_interior(alpha, beta, rec))
      return false;

    // Ray hits the 2D shape; set the rest of the hit record and return true. 
    rec.t = t;
    rec.p = intersection;
    rec.mat = mat;
    rec.set_face_normal(r, normal);
    
    return true; 
  }

  virtual bool is_interior(double a, double b, hit_record& rec) const
  {
    interval unit_interval = interval(0, 1);
    // Given the hit point in plane coordinates, return false if it is outside the
    // primitive, otherwise set the hit record UV coordinates and return true.

    if (!unit_interval.contains(a) || !unit_interval.contains(b))
      return false;

    rec.u = a;
    rec.v = b;

    return true; 
  }
  
  point3 Q;
  vec3 u, v;
  vec3 w; 
  shared_ptr<material> mat;
  aabb bbox;
  vec3 normal;
  double D; 
};

/*
struct tri: public quad
{
  tri(const point3& o, const vec3& aa, const vec3& ab, shared_ptr<material> m):
    quad(o, aa, ab, m) {}

  virtual bool is_interior(double a, double b, hit_record& rec) const override
  {
    if ((a < 0) || (b < 0) || (a + b > 1))
      return false;

    rec.u = a;
    rec.v = b;

    return true; 
  }
};

struct ellipse: public quad
{
  ellipse(const point3& center,
	  const vec3& side_A,
	  const vec3& side_B,
	  shared_ptr<material> m):
    quad(center, side_A, side_B, m) {}

  virtual bool set_bounding_box() override
  {
    bbox = aabb(plane_origin - axis_A - axis_B, plane_origin + axis_A + axis_B).pad();
  }

  virtual bool is_interior(double a, double b, hit_record& rec) const override
  {
    if ((a*a + b*b) > 1)
      return false;

    rec.u = a/2 + 0.5;
    rec.v = b/2 + 0.5;

    return true; 
  }
};

struct annulus: public quad
{
  annulus(const point3& center,
	  const vec3& side_A,
	  const vec3& side_B,
	  double _inner,
	  shared_ptr<material> m):
    quad(center, side_A, side_B, m), inner(_inner) {}

  virtual void set_bounding_box() override
  {
    bbox = aabb(plane_origin - axis_A - axis_B, plane_origin + axis_A + axis_B).pad();
  }

  virtual bool is_interior(double a, double b, hit_record& rec) const override
  {
    auto center_dist = sqrt(a*a + b*b);
    if ((center_dist < inner) || (center_dist > 1))
      return false;

    rec.u = a/2 + 0.5;
    rec.v = b/2 + 0.5;
    
    return true;
  }

  double inner; 
};
*/
#endif
