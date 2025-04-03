#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

struct hittable_list: public hittable
{
  static const int MAX_OBJECTS = 100; 
  static hittable* objects[MAX_OBJECTS];
  static int size;
 
  hittable_list() {}
  hittable_list(hittable& object) { add(object); }

  void clear()
  {
    for (int i = 0; i < size; i++)
      {
	delete objects[i];
	objects[i] = nullptr;
      }

    size = 0;
  }
  
  void add(hittable& object)
  {
    objects[size++] = &object; 
  }

  bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override
  {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto& object: objects)
      {
	if (object->hit(r, ray_tmin, closest_so_far, temp_rec))
	  {
	    hit_anything = true;
	    closest_so_far = temp_rec.t;
	    rec = temp_rec; 
	  }
      }

    return hit_anything; 
  }
};

int hittable_list::size = 0;
hittable* hittable_list::objects[hittable_list::MAX_OBJECTS] = { nullptr };

#endif
