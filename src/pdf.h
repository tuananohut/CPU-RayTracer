#ifndef PDF_H
#define PDF_H

#include "onb.h"

struct pdf
{
  virtual ~pdf();

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

#endif
