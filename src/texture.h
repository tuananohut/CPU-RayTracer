#ifndef TEXTURE_H
#define TEXTURE_H

#include "perlin.h"
#include "rtw_stb_image.h"

struct texture
{
  virtual ~texture() = default;

  virtual color value(double u, double v, const point3& p) const = 0;
};

struct solid_color: public texture
{
 solid_color(const color& albedo):
  albedo(albedo) {}

 solid_color(double red, double green, double blue):
  solid_color(color(red, green, blue)) {}

  color value(double u, double v, const point3& p) const override
  {
    return albedo; 
  }

  color albedo; 
};

struct checker_texture: public texture
{
 checker_texture(double scale, shared_ptr<texture> even, shared_ptr<texture> odd):
  inv_scale(1. / scale), even(even), odd(odd) {}

 checker_texture(double scale, const color& c1, const color& c2):
  checker_texture(scale, make_shared<solid_color>(c1), make_shared<solid_color>(c2)) {}

  color value(double u, double v, const point3& p) const override
  {
    auto xInteger = int(std::floor(inv_scale * p.x()));
    auto yInteger = int(std::floor(inv_scale * p.y()));
    auto zInteger = int(std::floor(inv_scale * p.z()));

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

    return isEven ? even->value(u, v, p): odd->value(u, v, p);
  }

  double inv_scale;
  shared_ptr<texture> even;
  shared_ptr<texture> odd; 
};

struct image_texture: public texture
{
  image_texture(const char* filename):
    image(filename) {}

  color value(double u, double v, const point3& p) const override
  {
    // If we have no texture data, then return solid cyan as a  debugging aid.
    if (image.height() <= 0)
      return color(0, 1, 1);

    // Clamp input texture coordinates to [0, 1] x [1, 0]
    u = interval(0, 1).clamp(u);
    v = 1. - interval(0, 1).clamp(v); // Flip V to image coordinates

    auto i = int(u * image.width());
    auto j = int(v * image.height());
    auto pixel = image.pixel_data(i, j);

    auto color_scale = 1. / 255.;

    return color(color_scale*pixel[0],
		 color_scale*pixel[1],
		 color_scale*pixel[2]);
  }

  rtw_image image; 
};

struct noise_texture: public texture
{
  noise_texture() {}

  color value(double u, double v, const point3& p) const override
  {
    return color(1, 1, 1) * noise.noise(p);
  }

  perlin noise; 
};

#endif
