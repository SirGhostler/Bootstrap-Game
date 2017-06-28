#include "AABB.h"

AABB::AABB()
{
	v2Position = Vector2();
	v2Extents = Vector2();
}

AABB::AABB(const Vector2 a_v2Postion, const Vector2 a_v2Extents)
{
	v2Position = a_v2Extents;
	v2Extents = a_v2Extents;
}

AABB::AABB(const float a_fPosX, const float a_fPosY, const float a_fHalfX, const float a_fHalfY)
{
	v2Position = Vector2(a_fPosX, a_fPosY);
	v2Extents = Vector2(a_fHalfX, a_fHalfY);
}

bool AABB::CollisionCheck(const AABB& a_AABB, const Vector2& a_v2Point)
{
	// max < point || point < min = no collision
	return
	   !((a_AABB.x + a_AABB.halfWidth < a_v2Point.v2x) || // If this, no collision
		(a_AABB.y + a_AABB.halfHeight > a_v2Point.v2y) ||
		(a_AABB.x - a_AABB.halfWidth  > a_v2Point.v2x) ||
		(a_AABB.y - a_AABB.halfHeight > a_v2Point.v2y));
}

bool AABB::CollisionCheck(const AABB& a_AABB_LHS, const AABB& a_AABB_RHS)
{
	return 
		!((a_AABB_LHS.x + a_AABB_LHS.halfWidth < a_AABB_RHS.x - a_AABB_RHS.halfWidth) ||
		(a_AABB_LHS.y + a_AABB_LHS.halfHeight < a_AABB_RHS.y - a_AABB_RHS.halfWidth) ||
		(a_AABB_LHS.x - a_AABB_LHS.halfWidth  > a_AABB_RHS.x + a_AABB_RHS.halfWidth) ||
		(a_AABB_LHS.y - a_AABB_LHS.halfHeight > a_AABB_RHS.y + a_AABB_RHS.halfWidth));
}

bool AABB::CollidesWith(const Vector2& a_v2Point) const
{
	return CollisionCheck(*this, a_v2Point);
}
bool AABB::CollidesWith(const AABB& a_AABB_RHS) const
{
	return CollisionCheck(*this, a_AABB_RHS);
}