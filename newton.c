// 
//  Newton Voyage - PSP homebrew game
//              by Sebastian Mihai, 2014
//              http://sebastianmihai.com
// 
// Newton Voyage is a two-week project on the Sony PSP. After finishing
// Geoincursion on the Nintendo DS, I wanted to take on a smaller project
// on a different platform. My theme from the start was "space-something
// with limited controls".
//
// The two-week interval includes figuring out the PSP, not leaving much
// time for code polish; the source code isn't as polished as that of my other games :)
// 


#include <time.h>
#include <pspkernel.h>

#include "platform.h"
#include "types.h"
#include "entities.h"
#include "input.h"
#include "levels.h"

void runLevel( struct Planet* planets, int numPlanets );

#define FRAMES_PER_SECOND ( 60.0f )
#define CLOCKS_PER_FRAME ( CLOCKS_PER_SEC / FRAMES_PER_SECOND )

PSP_MODULE_INFO( "Newton Voyage", 0, 1, 1 );
PSP_MAIN_THREAD_ATTR( THREAD_ATTR_USER );

int main( int argc, char* argv[] ) {
	platform_initialize();
	
	// current level definition
	struct Planet planets[ 16 ];
	int numPlanets;
	
	while( platform_isGameRunning() ) { 
		levelOne( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelTwo( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelThree( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelFour( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelFive( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelSix( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelSeven( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelEight( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelNine( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelTen( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelEleven( planets, &numPlanets );
		runLevel( planets, numPlanets );
		levelTwelve( planets, &numPlanets );
		runLevel( planets, numPlanets );
	}

	platform_shutdown();
	
	return 0;
}

// return when player launches the ship
void runPressToStart( 
	struct Planet* planets, 
	int numPlanets, 
	struct Sprite* launchArea, 
	struct GameObject* ship,
	struct Sprite* goal
	) {
	struct Sprite pressToStart = entity_makePressToStart();
	struct Sprite orientShip = entity_makeOrientShip();

	while( platform_isGameRunning() ) { 
		input_read();
		platform_preFrame();
		
		entity_renderSprite( launchArea );
		
		if( !input_isPressed( BUTTON_X ) ) {
			entity_renderSprite( &pressToStart );
			entity_renderSprite( &orientShip );
		}
		
		entity_renderSprite( goal );
		int i;
		for( i = 0; i < numPlanets; i++ ) {
			entity_renderSprite( &planets[ i ].sprite );
		}
		entity_renderSprite( &ship->sprite );
		
		platform_postFrame();
		
		if( input_isPressed( BUTTON_X ) ) {
			return;
		}
	}
}

// return when level is completed, since the player can retry a level indefinitely
void runLevel( struct Planet* planets, int numPlanets ) {

	// keep repeating level
	while( platform_isGameRunning() ) { 
	
		struct Sprite launchArea = entity_makeLaunchArea();
		struct GameObject ship = entity_makeGameObject();
		struct Sprite goal = entity_makeGoal();
	
		runPressToStart( planets, numPlanets, &launchArea, &ship, &goal );

		short hasLeftLaunchArea = 0;
		short hasCollided = 0;
		short committedUp = 0;
		short committedDown = 0;
		clock_t startTime;
		// keep repeating frame
		while( platform_isGameRunning() ) { 
			startTime = clock();
			
			if( ship.sprite.x >= -1.5f ) {
				hasLeftLaunchArea = 1;
			}
			
			// only steer when in launch zone
			if( !hasLeftLaunchArea ) {
				input_read();
				float maxAngle = 0.8f;
				float angleIncrement = 0.05f;
				if( input_isPressed( PAD_UP ) && !committedDown && ship.sprite.angle < maxAngle ) {
					ship.sprite.angle += angleIncrement;
					entity_recalculateVelocity( &ship );
					committedUp = 1;
				}
				if( input_isPressed( PAD_DOWN ) && !committedUp && ship.sprite.angle > -1.0f * maxAngle ) {
					ship.sprite.angle -= angleIncrement;
					entity_recalculateVelocity( &ship );
					committedDown = 1;
				}
			}
		
			platform_preFrame();
			
			entity_renderSprite( &launchArea );
			entity_renderSprite( &goal );

			int i;
			for( i = 0; i < numPlanets; i++ ) {
				// did we collide with a planet?
				if( entity_isRadialCollisionBetween( &ship.sprite, &planets[ i ].sprite ) ) {
					hasCollided = 1;
					break;
				}
			
				entity_renderSprite( &planets[ i ].sprite );
				ScePspFVector2 acceleration = entity_getGravityEffect( &ship, planets + i );
				entity_applyAcceleration( &ship, &acceleration );
			}
			
			entity_moveGameObject( &ship );
			entity_renderSprite( &ship.sprite );
			
			platform_postFrame();
			
			// did we collide with the goal?
			if( entity_isRadialCollisionBetween( &ship.sprite, &goal ) ) {
				return;
			}
			
			// did we go out of bounds?
			float verticalLimit = 1.7f;
			float horizontalLimit = 2.9f;
			if( ship.sprite.x - ship.sprite.radius < -1.0f * horizontalLimit ) {
				break;
			}
			if( ship.sprite.x + ship.sprite.radius > horizontalLimit ) {
				break;
			}
			if( ship.sprite.y - ship.sprite.radius < -1.0f * verticalLimit ) {
				break;
			}
			if( ship.sprite.y + ship.sprite.radius > verticalLimit ) {
				break;
			}
			
			if( hasCollided ) {
				break;
			}
			
			double clocksPassed = (double) ( clock() - startTime );
			while( clocksPassed < CLOCKS_PER_FRAME ) {
				clocksPassed = (double) ( clock() - startTime );
			}
		}
	}
}
