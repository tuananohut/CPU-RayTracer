#ifndef PDF_H
#define PDF_H

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

#endif
