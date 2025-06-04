#ifndef PDF_H
#define PDF_H

#include "hittable_list.h"
#include "onb.h"

struct pdf
{
  virtual ~pdf() {}

  virtual double value(const vec3& direction) const = 0;
  virtual vec3 generate() const = 0;
};

struct sphere_pdf: public pdf
{
  sphere_pdf() {}

  double value(const vec3& direction) const override
  {
    return 1 / (4 * pi);
  }

  vec3 generate() const override
  {
    return random_unit_vector();
  }
};

struct cosine_pdf: public pdf
{
  cosine_pdf(const vec3& w):
    uvw(w) {}

  double value(const vec3& direction) const override
  {
    auto cosine_theta = dot(unit_vector(direction), uvw.w());
    return std::fmax(0, cosine_theta/pi); 
  }

  vec3 generate() const override
  {
    return uvw.transform(random_cosine_direction()); 
  }

  onb uvw; 
};

struct hittable_pdf: public pdf
{
  hittable_pdf(const hittable& objects, const point3& origin):
    objects(objects), origin(origin) {}

  double value(const vec3& direction) const override
  {
    return objects.pdf_value(origin, direction); 
  }

  vec3 generate() const override
  {
    return objects.random(origin); 
  }

  const hittable& objects;
  point3 origin; 
};

struct mixture_pdf: public pdf
{
  mixture_pdf(shared_ptr<pdf> p0, shared_ptr<pdf> p1)
  {
    p[0] = p0;
    p[1] = p1;
  }

  double value(const vec3& direction) const override
  {
    return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
  }

  vec3 generate() const override
  {
    if (random_double() < 0.5)
      return p[0]->generate();
    else
      return p[1]->generate();
  }

  shared_ptr<pdf> p[2];
};

#endif
