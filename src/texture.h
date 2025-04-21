#ifndef TEXTURE_H
#define TEXTURE_H

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

#endif
