#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"

color ray_color(const ray& r, const hittable& world)
{
  hit_record rec;
  if (world.hit(r, interval(0, infinity), rec))
    {
      return 0.5 * (rec.normal + color(1, 1, 1));
    }
  
  vec3 unit_direction = unit_vector(r.direction());
  auto a = .5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.847, 0.106, 0.376);
}

int main()
{
  hittable_list world;

  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera cam;

  cam.aspect_ratio = 16.0/9.0;
  cam.image_width = 400;

  cam.render(world);
}
