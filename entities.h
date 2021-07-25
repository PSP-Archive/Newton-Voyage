#ifndef __ENTITIES___H__
#define __ENTITIES___H__

#include "types.h"
#include <psptypes.h>

//
// Game entities
//

#ifdef __cplusplus
extern "C" {
#endif

int entity_isRadialCollisionBetween( struct Sprite* left, struct Sprite* right );
void entity_recalculateVelocity( struct GameObject* gameObject );

void entity_applyAcceleration( struct GameObject* gameObject, ScePspFVector2* acceleration );

void entity_moveGameObject( struct GameObject* gameObject );
void entity_renderSprite( struct Sprite* sprite );

struct GameObject entity_makeGameObject();
struct Planet entity_makePlanet( int isRepulsive, float radius,	float x, float y );
struct Sprite entity_makeLaunchArea();
struct Sprite entity_makePressToStart();
struct Sprite entity_makeOrientShip();
struct Sprite entity_makeGoal();
ScePspFVector2 entity_getGravityEffect( struct GameObject* gameObject, struct Planet* planet );

#ifdef __cplusplus
}
#endif

#endif