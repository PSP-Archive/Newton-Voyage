#include "platform.h"
#include "entities.h"
#include <math.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

#define RED 0xff0000ff
#define GREEN 0xff00cc00
#define BROWN 0xff053f57
#define BLUE 0xffff0000
#define WHITE 0xffffffff

extern unsigned char texship_start[];
extern unsigned char texplanet_start[];
extern unsigned char texpixel_start[];
extern unsigned char texpress_start[];
extern unsigned char texmove_start[];
extern unsigned char texgoal_start[];

// used by platform (PSP) to represent vertices
struct Vertex {
	float u, v;
	unsigned int colour;
	float x, y, z;
};

float distanceBetweenCentresOf( struct Sprite* left, struct Sprite* right ) {
	float deltaX = left->x - right->x;
	float deltaY = left->y - right->y;
	float distanceBetweenCentres = sqrt( 
		deltaX * deltaX +
		deltaY * deltaY
		);
	return distanceBetweenCentres;
}

int entity_isRadialCollisionBetween( struct Sprite* left, struct Sprite* right ) {
	float radiiSum = left->radius + right->radius;
	float distanceBetweenCentres = distanceBetweenCentresOf( left, right );
	
	return distanceBetweenCentres - radiiSum <= 0.0f;
}

// from angle
void entity_recalculateVelocity( struct GameObject* gameObject ) {
	float speed = sqrt( 
		gameObject->velocity.x * gameObject->velocity.x +
		gameObject->velocity.y * gameObject->velocity.y
		);
	
	gameObject->velocity.x = speed * cos( gameObject->sprite.angle );
	gameObject->velocity.y = speed * sin( gameObject->sprite.angle );
}

// from velocity
void RecalculateAngle( struct GameObject* gameObject ) {
	gameObject->sprite.angle = platform_safeAtan2( 
		gameObject->velocity.y,
		gameObject->velocity.x
		);
}

// apply acceleration to a game object
void entity_applyAcceleration( struct GameObject* gameObject, ScePspFVector2* acceleration ) { 
	gameObject->velocity.x += acceleration->x;
	gameObject->velocity.y += acceleration->y;
	RecalculateAngle( gameObject );
}

void entity_moveGameObject( struct GameObject* gameObject ) {
	gameObject->sprite.x += gameObject->velocity.x;
	gameObject->sprite.y += gameObject->velocity.y;
	RecalculateAngle( gameObject );
}

void entity_renderSprite( struct Sprite* sprite ) {
	u8 vertexCount = 2;
	// allocate memory for two corners of the sprite (sufficient to draw it)
	struct Vertex* vertices = sceGuGetMemory( vertexCount * sizeof( struct Vertex ) );
	
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;
	vertices[0].colour = sprite->colour;
	vertices[0].x = -1.0f * sprite->radius;
	vertices[0].y = sprite->radius;
	vertices[0].z = sprite->z;
	
	vertices[1].u = 1.0f;
	vertices[1].v = 1.0f;
	vertices[1].colour = sprite->colour;
	vertices[1].x = sprite->radius;
	vertices[1].y = -1.0f * sprite->radius;
	vertices[1].z = sprite->z;
	
	// 16 bits per pixel, 5 for R, G, B
	sceGuTexMode( GU_PSM_5551, 0, 0, 0 );
	sceGuTexImage(
		0,
		sprite->texture.width,
		sprite->texture.height,
		sprite->texture.width,
		sprite->texture.data
		); // width, height, buffer width, tbp
		
	sceGuTexFunc( GU_TFX_MODULATE, GU_TCC_RGBA );
	sceGuTexFilter( GU_NEAREST, GU_NEAREST );
	sceGuTexWrap( GU_CLAMP, GU_CLAMP );
	sceGuTexScale( 1, 1 );
	sceGuTexOffset( 0, 0 );
	
	sceGumPushMatrix();
	sceGumLoadIdentity();
	
	ScePspFVector3 spritePosition = { sprite->x, sprite->y, sprite->z };
	sceGumTranslate( &spritePosition );
	
	sceGumDrawArray(
		GU_SPRITES, 
		GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D,
		vertexCount,
		0,
		vertices
		);
	
	sceGumPopMatrix();
}

struct GameObject entity_makeGameObject() {
	struct GameObject gameObject;
	gameObject.sprite.radius = 0.1f;
	gameObject.sprite.x = -2.8f;
	gameObject.sprite.y = 0.0f;
	gameObject.sprite.z = -1.0f;
	gameObject.sprite.colour = WHITE;
	gameObject.sprite.texture.data = texship_start;
	gameObject.sprite.texture.width = 32;
	gameObject.sprite.texture.height = 32;
	gameObject.velocity.x = 0.02f;
	gameObject.velocity.y = 0.0f;
	RecalculateAngle( &gameObject );
	
	return gameObject;
}

struct Planet entity_makePlanet( int isRepulsive, float radius,	float x, float y ) {
	struct Planet planet;
	planet.sprite.radius = radius;
	planet.sprite.x = x;
	planet.sprite.y = y;
	planet.sprite.z = -1.0f;
	planet.sprite.colour = isRepulsive ? RED : GREEN;
	planet.sprite.texture.data = texplanet_start;
	planet.sprite.texture.width = 32;
	planet.sprite.texture.height = 32;
	planet.isRepulsive = isRepulsive;
	planet.sprite.angle = 0.0f;
	
	return planet;
}

struct Sprite entity_makeLaunchArea() {
	struct Sprite launchArea;
	launchArea.radius = 0.8f;
	launchArea.x = -1.6f;
	launchArea.y = 0.0f;
	launchArea.z = -0.5f;
	launchArea.colour = BROWN;
	launchArea.angle = 0.0f;
	launchArea.texture.width = 1;
	launchArea.texture.height = 1;
	launchArea.texture.data = texpixel_start;
	
	return launchArea;
}

struct Sprite entity_makeGoal() {
	struct Sprite goal;
	goal.radius = 0.2f;
	goal.x = 2.53f;
	goal.y = 0.0f;
	goal.z = -1.0f;
	goal.colour = WHITE;
	goal.angle = 0.0f;
	goal.texture.width = 32;
	goal.texture.height = 32;
	goal.texture.data = texgoal_start;
	
	return goal;
}

struct Sprite entity_makePressToStart() {
	struct Sprite info;
	info.radius = 0.6f;
	info.x = -2.05f;
	info.y = -1.05f;
	info.z = -0.9f;
	info.colour = WHITE;
	info.angle = 0.0f;
	info.texture.width = 64;
	info.texture.height = 32;
	info.texture.data = texpress_start;
	
	return info;
}

struct Sprite entity_makeOrientShip() {
	struct Sprite info;
	info.radius = 0.65f;
	info.x = -1.95f;
	info.y = 0.95f;
	info.z = -0.9f;
	info.colour = WHITE;
	info.angle = 0.0f;
	info.texture.width = 128;
	info.texture.height = 64;
	info.texture.data = texmove_start;
	
	return info;
}

// returns a acceleration vector of the effect of a planet on a game object
ScePspFVector2 entity_getGravityEffect( struct GameObject* gameObject, struct Planet* planet ) {
	float gConstant = 0.03f;
	float density = 0.2f;
	
	float planetRadius = planet->sprite.radius;
	float planetMass =  
		4.0f / 3.0f *
		planetRadius * planetRadius * planetRadius * 
		3.14159265f * 
		density;
	
	float distanceBetweenCentres = distanceBetweenCentresOf( &gameObject->sprite, &planet->sprite );
	
	float gameObjectRadius = gameObject->sprite.radius;
	float gameObjectMass = 4.0f / 3.0f *
		gameObjectRadius * gameObjectRadius * gameObjectRadius *
		3.14159265f * 
		density;
	
	float force = 
		gConstant * gameObjectMass * planetMass /
		( distanceBetweenCentres * distanceBetweenCentres );

	float accelerationAbsoluteValue = force / gameObjectMass;
	
	float deltaX = gameObject->sprite.x - planet->sprite.x;
	float deltaY = gameObject->sprite.y - planet->sprite.y;
	float length = sqrt( deltaX * deltaX + deltaY * deltaY );
	deltaX = deltaX / length;
	deltaY = deltaY / length;
	
	ScePspFVector2 result = { deltaX * accelerationAbsoluteValue, deltaY * accelerationAbsoluteValue };
	if( !planet->isRepulsive ) {
		result.x = -1.0f * result.x;
		result.y = -1.0f * result.y;
	}
	
	return result;
}
