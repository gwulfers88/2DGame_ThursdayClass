#ifndef VEC2_H
#define VEC2_H

#include "helper.h"
#include <math.h>

//pixel coordinates
struct Vec2
{
	Vec2() : r(x), th(y) { }
	Vec2(r32 xx, r32 yy) : x(xx), y(yy), r(x), th(y) {}
	Vec2(const Vec2& a) : x(a.x), y(a.y), r(x), th(y) {}

	Vec2 operator=(const Vec2 &b)
	{
		x = b.x;
		y = b.y;
		return b;
	}

	r32 x;
	r32 y;

	r32& r;
	r32& th;
};

static Vec2 operator+(const Vec2 &a, const Vec2 &b)
{
	Vec2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

static Vec2 operator+(const Vec2 &a, const r32 &b)
{
	Vec2 result;
	result = a + b;
	return result;
}

static Vec2 operator-(const Vec2 &a, const Vec2 &b)
{
	Vec2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

static Vec2 operator*(const Vec2 &a, r32 c)
{
	Vec2 result = a;
	result.x *= c;
	result.y *= c;
	return result;
}

static Vec2 operator*(r32 c, const Vec2 &a)
{
	Vec2 result = a;
	result.x *= c;
	result.y *= c;
	return result;
}

static Vec2 operator/(const Vec2 &a, r32 c)
{
	Vec2 result = a;
	result.x /= c;
	result.y /= c;
	return result;
}

inline r32 Square(r32 A)
{
	r32 result;
	result = A * A;
	return result;
}

inline r32 Dot(Vec2 A, Vec2 B)
{
	r32 result = A.x * B.x + A.y * B.y;
	return result;
}

inline r32 MagnitudeSqr(Vec2 A)
{
	r32 result = Dot(A, A);
	return result;
}

inline void Normalize(Vec2* A)
{
	r32 magnitude = sqrt(MagnitudeSqr(*A));
	if (magnitude > 0.0f)
	{
		*A = *A / magnitude;
	}
}

#endif