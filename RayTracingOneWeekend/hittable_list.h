#pragma once
#include <memory>
#include<vector>

#include "hittable.h"

using std::shared_ptr; 
using std::make_shared; 

class hittable_list : public hittable {
public: 
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	/// <summary>
	/// Removes all objects from hittable_list instance
	/// </summary>
	void clear() { objects.clear(); }
	/// <summary>
	/// Add single object to hittable_list instance
	/// </summary>
	/// <param name="object"></param>
	void add(shared_ptr<hittable> object) {objects.push_back(object); }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	std::vector<shared_ptr<hittable>> objects;
};


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record object_rec; 
	bool hit_anything = false; 
	auto closest_so_far = t_max;

	// Interating through ever object in hitttable_list to determine the cloest hit intersectio
	for (const auto& object : objects) {
		// Determines if input parameter ray intersects with object
		// and is closer than closest know intersection
		if (object->hit(r, t_min, closest_so_far, object_rec)) {
			hit_anything = true; 
			closest_so_far = object_rec.t; 
			rec = object_rec; // updates the return parameter
		}
	}
	return hit_anything;
}