#ifndef __LEVELS___H__
#define __LEVELS___H__

#include "types.h"

//
// Populates levels with planets
//

#ifdef __cplusplus
extern "C" {
#endif

// populate planets for each level
void levelOne( struct Planet* planets, int* numPlanets );
void levelTwo( struct Planet* planets, int* numPlanets );
void levelThree( struct Planet* planets, int* numPlanets );
void levelFour( struct Planet* planets, int* numPlanets );
void levelFive( struct Planet* planets, int* numPlanets );
void levelSix( struct Planet* planets, int* numPlanets );
void levelSeven( struct Planet* planets, int* numPlanets );
void levelEight( struct Planet* planets, int* numPlanets );
void levelNine( struct Planet* planets, int* numPlanets );
void levelTen( struct Planet* planets, int* numPlanets );
void levelEleven( struct Planet* planets, int* numPlanets );
void levelTwelve( struct Planet* planets, int* numPlanets );

#ifdef __cplusplus
}
#endif

#endif