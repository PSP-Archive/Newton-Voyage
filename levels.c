#include "levels.h"
#include "entities.h"

void levelOne( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 0;
}

void levelTwo( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 1;
	planets[0] = entity_makePlanet( 0, 0.3f, 0.8f, -0.6f );
}

void levelThree( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 1;
	planets[0] = entity_makePlanet( 1, 0.16f, 1.3f, 1.3f );
}

void levelFour( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 1;
	planets[0] = entity_makePlanet( 0, 0.4f, 0.8f, 0.0f );
}

void levelFive( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 2;
	planets[0] = entity_makePlanet( 0, 0.35f, 0.8f, -1.0f );
	planets[1] = entity_makePlanet( 0, 0.4f, 0.8f, 0.8f );
}

void levelSix( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 3;
	planets[0] = entity_makePlanet( 1, 0.1f, -0.5f, -1.0f );
	planets[1] = entity_makePlanet( 1, 0.14f, 1.3f, -1.0f );
	planets[2] = entity_makePlanet( 1, 0.12f, 0.9f, 1.0f );
}

void levelSeven( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 4;
	planets[0] = entity_makePlanet( 0, 0.3f, 0.5f, 0.0f );
	planets[1] = entity_makePlanet( 1, 0.14f, 1.3f, -1.0f );
	planets[2] = entity_makePlanet( 1, 0.275f, 0.9f, 1.0f );
	planets[3] = entity_makePlanet( 0, 0.25f, 2.3f, -1.0f );
}

void levelEight( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 4;
	planets[0] = entity_makePlanet( 1, 0.2f, 0.5f, 0.0f );
	planets[1] = entity_makePlanet( 0, 0.14f, 1.3f, -1.0f );
	planets[2] = entity_makePlanet( 0, 0.275f, 0.9f, 1.0f );
	planets[3] = entity_makePlanet( 1, 0.25f, 2.3f, -1.0f );
}

void levelNine( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 7;
	planets[0] = entity_makePlanet( 0, 0.2f, -1.3f, 0.0f );
	planets[1] = entity_makePlanet( 0, 0.2f, -1.0f, 0.0f );
	planets[2] = entity_makePlanet( 0, 0.2f, -0.7f, 0.0f );
	planets[3] = entity_makePlanet( 0, 0.2f, -0.4f, 0.0f );
	planets[4] = entity_makePlanet( 0, 0.2f, -0.1f, 0.0f );
	
	planets[5] = entity_makePlanet( 0, 0.2f, 2.1f, 0.8f );
	planets[6] = entity_makePlanet( 0, 0.2f, 2.1f, -0.8f );
}

void levelTen( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 7;
	planets[0] = entity_makePlanet( 0, 0.1f, -1.3f, -0.6f );
	planets[1] = entity_makePlanet( 0, 0.1f, -1.0f, 0.6f );
	planets[2] = entity_makePlanet( 0, 0.1f, -0.7f, -0.6f );
	planets[3] = entity_makePlanet( 0, 0.1f, -0.4f, 0.6f );
	planets[4] = entity_makePlanet( 0, 0.1f, -0.1f, -0.6f );
	planets[5] = entity_makePlanet( 0, 0.1f, 0.2f, 0.6f );
	planets[6] = entity_makePlanet( 0, 0.1f, 0.5f, -0.6f );
}

void levelEleven( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 2;
	planets[0] = entity_makePlanet( 1, 0.2f, -2.0f, -1.6f );
	planets[1] = entity_makePlanet( 1, 0.1f, 1.0f, 0.2f );
}

void levelTwelve( struct Planet* planets, int* numPlanets ) {
	*numPlanets = 5;
	planets[0] = entity_makePlanet( 1, 0.1f, 1.0f, -0.2f );
	planets[1] = entity_makePlanet( 1, 0.1f, 1.0f, 0.2f );
	planets[2] = entity_makePlanet( 1, 0.1f, 1.6f, -1.5f );
	planets[3] = entity_makePlanet( 1, 0.1f, 1.6f, 1.5f );
	planets[4] = entity_makePlanet( 0, 0.2f, 1.6f, 0.0f );
}