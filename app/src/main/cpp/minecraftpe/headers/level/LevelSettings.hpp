#pragma once
#include <_types.h>

struct LevelSettings
{
	int32_t seed, gameType;
	//Terrain generator of the new world (a TerrainGeneratorType). 0 is the original MCPE 0.8.1 one.
	int32_t terrainGenerator;

	LevelSettings(int seed, int gt, int terrainGenerator = 0) : seed(seed), gameType(gt), terrainGenerator(terrainGenerator){

	}
};
