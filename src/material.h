#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

struct material
{
  virtual ~material() = default;

  virtual bool scatter(const ray& r_in,
		       const hit_record& rec,
		       color& attenuation,
		       ray& scattered) const
  {
    return false; 
  }
};


// We chose always scatter
struct lambertian: public material
{
 lambertian(const color& albedo):
  albedo(albedo) {}

  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       color& attenuation,
	       ray& scattered) const override 
  {
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
      {
	scatter_direction = rec.normal; 
      }
   
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;

    // Third option: fixed probability p and attenuation albedo / p
      
    return true;
  }
  
  color albedo;
};

struct metal: public material
{
  metal(const color& albedo, double fuzz):
    albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       color& attenuation,
	       ray& scattered) const override
  {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
  }

  color albedo;
  double fuzz; 
};

#endif
