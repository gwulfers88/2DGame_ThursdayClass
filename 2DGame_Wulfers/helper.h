#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

typedef char		i8;
typedef short		i16;
typedef int			i32;
typedef long long	i64;

typedef float		r32;
typedef double		r64;

typedef int			b32;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

#define Assert(expression) if(!expression) { *(int*)0 = 0; }
#define ArrayCount(a) (sizeof(a) / sizeof(a[0])

//keys
namespace KEYS
{
	enum 
	{ 
		NONE = 0,
		MOUSE0 = 1 << 1,
		MOUSE1 = 1 << 2,
		UP = 1 << 3,
		DOWN = 1 << 4, 
		LEFT = 1 << 5,
		RIGHT = 1 << 6,
		SPACE = 1 << 7,
	};
	const i32 NUMKEYS = 7;
}

static const i32 FPS = 15;
