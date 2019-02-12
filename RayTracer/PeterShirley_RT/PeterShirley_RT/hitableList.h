#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class HitableList : public Hitable
{
public:
	HitableList() {};

	HitableList(Hitable** hitableList, int numHitables)
	{
		H = hitableList;
		S = numHitables;
	}

	bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override
	{
		HitRecord tempRecord;
		bool hitAnything = false;
		float closestT = tMax;
		
		for (int i = 0; i < S; i++)
		{
			if (H[i]->hit(ray, tMin, closestT, tempRecord))
			{
				hitAnything = true;
				closestT = tempRecord.t;
				rec = tempRecord;
			}
		}

		return hitAnything;
	}

private:
	Hitable** H;
	int S;
};

#endif