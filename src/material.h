#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "pdf.h"
#include "texture.h"

struct scatter_record
{
  color attenuation;
  shared_ptr<pdf> pdf_ptr;
  bool skip_pdf;
  ray skip_pdf_ray; 
};

struct material
{
  virtual ~material() = default;

  virtual color emitted(const ray& r_in,
			const hit_record& rec,
			double u, double v, const point3& p) const
  {
    return color(0, 0, 0); 
  }
  
  virtual bool scatter(const ray& r_in,
		       const hit_record& rec,
		       color& attenuation,
		       ray& scattered,
		       double& pdf) const
  {
    return false; 
  }

  virtual double scattering_pdf(const ray& r_in,
				const hit_record& rec,
				scatter_record& srec) const 
  {
    return 0; 
  }
};

// We chose always scatter
struct lambertian: public material
{
  lambertian(const color& albedo):
    tex(make_shared<solid_color>(albedo)) {}
  lambertian(shared_ptr<texture> tex):
    tex(tex) {}
  
  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       scatter_record& srec) const override 
  {
    srec.attenuation = tex->value(rec.u, rec.v, rec.p);
    srec.pdf_ptr = make_shared<cosine_pdf>(rec.normal);
    srec.skip_pdf = false; 
    
    return true;
  }

  double scattering_pdf(const ray& r_in,
			const hit_record& rec,
			const ray& scattered) const override
  {
    auto cos_theta = dot(rec.normal, unit_vector(scattered.direction()));
    return cos_theta < 0 ? 0 : cos_theta/pi; 
  }

  shared_ptr<texture> tex; 
};

struct metal: public material
{
  metal(const color& albedo, double fuzz):
    albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       color& attenuation,
	       ray& scattered,
	       double& pdf) const override
  {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected, r_in.time());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
  }

  color albedo;
  double fuzz; 
};

struct dielectric: public material
{
  dielectric(double refraction_index):
    refraction_index(refraction_index) {}

  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       color& attenuation,
	       ray& scattered,
	       double& pdf) const override
  {
    attenuation = color(1., 1., 1.);
    double ri = rec.front_face ? (1./refraction_index): refraction_index;
    
    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.);
    double sin_theta = std::sqrt(1. - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, ri) > random_double())
      {
	direction = reflect(unit_direction, rec.normal); 
      }
    else
      {
	direction = refract(unit_direction, rec.normal, ri); 
      }
    
    scattered = ray(rec.p, direction, r_in.time());
    return true; 
  }
  
  // Refractive index in vacuum or air, or the ratio of the material's refractive index
  // over the refractive index of the enclosing media
  double refraction_index;

  static double reflectance(double cosine, double refraction_index)
  {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0)*std::pow((1 - cosine), 5);
  }
};

struct diffuse_light: public material
{
  diffuse_light(shared_ptr<texture> tex):
    tex(tex) {}

  diffuse_light(const color& emit):
    tex(make_shared<solid_color>(emit)) {}

  color emitted(const ray& r_in,
		const hit_record& rec,
		double u, double v, const point3& p) const override
  {
    if (!rec.front_face)
      return color(0, 0, 0);
    return tex->value(u, v, p); 
  }

  shared_ptr<texture> tex; 
};

struct isotropic: public material
{
  isotropic(const color& albedo):
    tex(make_shared<solid_color>(albedo)) {}

  isotropic(shared_ptr<texture> tex):
    tex(tex) {}

  bool scatter(const ray& r_in,
	       const hit_record& rec,
	       scatter_record& srec) const override
  {
    srec.attenuation = tex->value(rec.u, rec.v, rec.p);
    srec.pdf_ptr = make_shared<sphere_pdf>();
    srec.skip_pdf = false; 
    
    return true; 
  }

  double scattering_pdf(const ray& r_in,
			const hit_record& rec,
			const ray& scattered) const override
  {
    return 1 / (4 * pi);
  }

  shared_ptr<texture> tex; 
};

#endif
