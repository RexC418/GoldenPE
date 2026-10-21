#pragma once
#include <level/gen/ChunkSource.hpp>
#include <level/gen/TerrainGenerator.hpp>

struct Level;

//1:1 port of the terrain generator of Minecraft Pre-Classic rd-132211 (Level.java):
//
//	for(int x = 0; x < w; ++x) for(int y = 0; y < d; ++y) for(int z = 0; z < h; ++z)
//		blocks[(y * h + z) * w + x] = (byte)(y <= d * 2 / 3 ? 1 : 0);
//
//with w = 256, h = 256 and d = 64 (RubyDung.java), and Chunk.java drawing the layer y == d * 2 / 3 as the grass one.
//So the world is 42 layers of stone (y = 0 to 41) with 1 layer of grass (y = 42) on top, each layer 1 block high and
//256 x 256 blocks wide. Everything above is air.
//
//The stone of rd-132211 is Cobblestone in MCPE 0.8.1 (its Stone block is a different one), the top layer is the Grass Block.
struct RD132211LevelSource : ChunkSource{
	struct Level* level;

	RD132211LevelSource(struct Level*);

	virtual ~RD132211LevelSource();
	virtual bool_t hasChunk(int32_t, int32_t);
	virtual struct LevelChunk* getChunk(int32_t, int32_t);
	virtual struct LevelChunk* create(int32_t, int32_t);
	virtual void postProcess(struct ChunkSource*, int32_t, int32_t);
	virtual bool_t tick();
	virtual bool_t shouldSave();
	virtual std::vector<Biome::MobSpawnerData> getMobsAt(const struct MobCategory&, int32_t, int32_t, int32_t);
	virtual std::string gatherStats();
};
