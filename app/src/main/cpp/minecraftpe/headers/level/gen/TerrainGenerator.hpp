#pragma once
#include <_types.h>

//Terrain generators a world can use.
//The generator of a world is saved in its level.dat as the int tag "TerrainGenerator".
enum TerrainGeneratorType {
	//Original MCPE 0.8.1 generator (RandomLevelSource).
	//It is also the one used by worlds saved before the Terrain Generation setting existed (they have no tag).
	TERRAIN_GENERATOR_MCPE_081 = 0,
	//Minecraft Pre-Classic rd-132211
	TERRAIN_GENERATOR_RD_132211 = 1
};

//Values of the rd-132211 world (RubyDung.java creates it with "new Level(256, 256, 64)")
struct RD132211 {
	enum {
		WIDTH = 256,				//Level.width  (X axis)
		LENGTH = 256,				//Level.height (Z axis)
		DEPTH = 64,					//Level.depth  (Y axis): blocks only exist, and can only be placed, from y = 0 to y = 63
		TOP_LAYER = DEPTH * 2 / 3	//The Level constructor fills every block with y <= depth * 2 / 3 (y = 42). The last layer is the grass one.
	};
};

struct TerrainGenerator {
	//Position, in the list of selectable generators, that is selected when nothing else was chosen
	static const int32_t DEFAULT_SELECTION = 0;

	//Generators that can be picked in Terrain Settings -> Terrain Generation, in the order the arrow buttons go through them
	static int32_t getSelectableCount();
	static int32_t getSelectableType(int32_t index);

	//Generator picked in the Terrain Settings screen for the next world that gets created
	static int32_t getSelectedIndex();
	static void setSelectedIndex(int32_t index);
	static int32_t getSelectedType();

	//Name of the version the generator belongs to
	static const char* getVersionName(int32_t type);
	static bool_t isValid(int32_t type);
	//true if outside of the world there is the void (no Invisible Bedrock walls) instead of the original world limits
	static bool_t hasVoidBorder(int32_t type);
	//Blocks can only exist and be placed below this height
	static int32_t getMaxBuildHeight(int32_t type);
};
