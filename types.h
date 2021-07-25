#ifndef ____TYPES_____H
#define ____TYPES_____H

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Texture {
	unsigned char* data;
	unsigned int width;
	unsigned int height;
};

// an orientable, renderable object
struct Sprite {
	struct Texture texture;
	float radius;
	float x, y, z;
	unsigned int colour;
	float angle;
};

// a movable entity
struct GameObject {
	struct Sprite sprite;
	ScePspFVector2 velocity;
};

// a fixed entity
struct Planet {
	struct Sprite sprite;
	int isRepulsive;
};

#ifdef __cplusplus
}
#endif

#endif