#pragma once
#include <level/chunk/LevelChunk.hpp>
#include <tile/Tile.hpp>

struct LevelChunk;
struct LevelConverters
{
	static bool_t v1_ClothIdToClothData(LevelChunk* a1) {
		uint8_t* tiles = a1->tiles;
		uint8_t blockID = Tile::cloth->blockID;
		int v3 = 0;
		bool v4 = 0;
		do {
			int v5 = tiles[v3];
			if ((uint32_t) ((v5 - 101)) <= 0xE) {
				tiles[v3] = blockID;
				uint8_t* data = a1->tileMeta.data;
				int8_t v7 = 116 - v5;
				uint8_t v8 = data[v3 >> 1];
				int8_t v9;
				if ((v3 & 1) != 0) {
					v9 = v8 & 0xF;
				} else {
					v9 = v8 & 0xF0;
				}
				uint8_t v10;
				if ((v3 & 1) != 0) {
					v10 = v9 | (16 * v7);
				} else {
					v10 = v7 | v9;
				}
				data[v3 >> 1] = v10;
				v4 = 1;
			}
			++v3;
		} while (v3 != 0x8000);
		return v4;
	}
};
