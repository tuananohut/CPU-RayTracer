#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "triangle.h"

triangle triangle = {point3(0, 1, -1), point3(-1, 0, -1), point3(1, 0, -1)};

double hit_sphere(const point3& center, double radius, const ray& r)
{
  vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius*radius;
  auto discriminant = h*h - a*c;

  if (discriminant < 0)
    {
      return -1.0;
    }
  else
    {
      return (h - std::sqrt(discriminant)) / a;
    }
}

color ray_color(const ray& r)
{
  const double infinity = std::numeric_limits<double>::infinity();
  
  auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
  if (t > 0.0)
    {
      vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
      return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    }
    
  vec3 unit_direction = unit_vector(r.direction());
  auto a = .5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.847, 0.106, 0.376);
}

int main()
{
  // Image
  auto aspect_ratio = 16. / 9.;
  int image_width = 400;

  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera

  auto focal_length = 1.;
  auto viewport_height = 2.;
  auto viewport_width = viewport_height * (double(image_width) / image_height); 
  auto camera_center = point3(0, 0, 0);

  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;
  
  auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length)
                             - viewport_u / 2
                             - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++)
    {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
      for (int i = 0; i < image_width; i++)
	{
	  auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
	  auto ray_direction = pixel_center - camera_center;
	  ray r(camera_center, ray_direction); 

	  color pixel_color = ray_color(r);
      	  write_color(std::cout, pixel_color);
	}
    }

  std::clog << "\rDone.                   \n";
}
