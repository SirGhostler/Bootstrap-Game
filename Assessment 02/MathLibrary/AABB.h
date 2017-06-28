#pragma once

#include "Vector2.h"

class AABB
{
public:

	union
	{
		struct
		{
			Vector2 v2Position;
			Vector2 v2Extents;
		};
		struct
		{
			float x, y, halfWidth, halfHeight;
		};
	};

	AABB();
	AABB(const Vector2 a_v2Postion, const Vector2 a_v2Extents);
	AABB(const float a_fPosX, const float a_fPosY, const float a_fHalfX, const float a_fHalfY);

	static bool CollisionCheck(const AABB& a_AABB, const Vector2& a_v2Position);
	static bool CollisionCheck(const AABB& a_AABB_LHS, const AABB& a_AABB_RHS);

	bool CollidesWith(const Vector2& a_v2Point) const;
	bool CollidesWith(const AABB& a_AABB_RHS) const;

private:

};

