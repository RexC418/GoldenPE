#include <level/gen/RD132211LevelSource.hpp>
#include <level/BiomeSource.hpp>
#include <level/Level.hpp>
#include <level/MobSpawner.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <tile/Tile.hpp>
#include <string.h>

RD132211LevelSource::RD132211LevelSource(struct Level* level) {
	this->level = level;
}
RD132211LevelSource::~RD132211LevelSource() {
}
bool_t RD132211LevelSource::hasChunk(int32_t x, int32_t z) {
	return 1;
}
struct LevelChunk* RD132211LevelSource::getChunk(int32_t chunkX, int32_t chunkZ) {
	return this->create(chunkX, chunkZ);
}
struct LevelChunk* RD132211LevelSource::create(int32_t chunkX, int32_t chunkZ) {
	//A chunk of MCPE is 16 x 128 x 16 blocks, stored as blocks[(x << 11) | (z << 7) | y]
	uint8_t* blocks = new uint8_t[0x8000u];
	memset(blocks, 0, 0x8000u);

	uint8_t stone = (uint8_t)Tile::stoneBrick->blockID; //Cobblestone. Stone (Tile::rock) is another block in MCPE 0.8.1
	uint8_t grass = (uint8_t)Tile::grass->blockID;
	for(int32_t x = 0; x < 16; ++x) {
		for(int32_t z = 0; z < 16; ++z) {
			uint8_t* column = &blocks[(x << 11) | (z << 7)];
			for(int32_t y = 0; y < RD132211::TOP_LAYER; ++y) { //y = 0 .. 41: 42 layers of stone
				column[y] = stone;
			}
			column[RD132211::TOP_LAYER] = grass; //y = 42: the grass layer. Everything above it stays air
		}
	}

	LevelChunk* chunk = new LevelChunk(this->level, blocks, chunkX, chunkZ);
	chunk->recalcHeightmap();
	return chunk;
}
void RD132211LevelSource::postProcess(struct ChunkSource*, int32_t, int32_t) {
	//rd-132211 only has the terrain: no trees, ores, caves, water...
}
bool_t RD132211LevelSource::tick() {
	return 0;
}
bool_t RD132211LevelSource::shouldSave() {
	return 1;
}
std::vector<Biome::MobSpawnerData> RD132211LevelSource::getMobsAt(const struct MobCategory& category, int32_t x, int32_t y, int32_t z) {
	//Mob spawning is not part of the terrain, so it works like in the original generator
	BiomeSource* bs = this->level->getBiomeSource();
	if(bs) {
		Biome* biome = bs->getBiome(x, z);
		if(biome) {
			return std::vector<Biome::MobSpawnerData>(*biome->getMobs(category));
		}
	}
	return std::vector<Biome::MobSpawnerData>();
}
std::string RD132211LevelSource::gatherStats() {
	return "RD132211LevelSource";
}
