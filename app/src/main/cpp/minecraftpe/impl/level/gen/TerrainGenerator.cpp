#include <level/gen/TerrainGenerator.hpp>

//Generators shown in "Terrain Settings -> Terrain Generation", in the order the arrow buttons go through them.
//For now there is only the one of rd-132211. To add the generator of another version: add its id to TerrainGeneratorType,
//list it here, and give it a name in getVersionName().
static const int32_t selectableGenerators[] = {
	TERRAIN_GENERATOR_RD_132211};

static int32_t selectedIndex = TerrainGenerator::DEFAULT_SELECTION;

int32_t TerrainGenerator::getSelectableCount() {
	return (int32_t)(sizeof(selectableGenerators) / sizeof(selectableGenerators[0]));
}
int32_t TerrainGenerator::getSelectableType(int32_t index) {
	if(index < 0 || index >= getSelectableCount()) index = DEFAULT_SELECTION;
	return selectableGenerators[index];
}
int32_t TerrainGenerator::getSelectedIndex() {
	return selectedIndex;
}
void TerrainGenerator::setSelectedIndex(int32_t index) {
	int32_t count = getSelectableCount();
	if(count <= 0) return;
	selectedIndex = ((index % count) + count) % count;
}
int32_t TerrainGenerator::getSelectedType() {
	return getSelectableType(selectedIndex);
}
const char* TerrainGenerator::getVersionName(int32_t type) {
	switch(type) {
		case TERRAIN_GENERATOR_RD_132211:
			return "RD-132211";
		default:
			return "MCPE 0.8.1";
	}
}
bool_t TerrainGenerator::isValid(int32_t type) {
	return type == TERRAIN_GENERATOR_MCPE_081 || type == TERRAIN_GENERATOR_RD_132211;
}
bool_t TerrainGenerator::hasVoidBorder(int32_t type) {
	return type == TERRAIN_GENERATOR_RD_132211;
}
int32_t TerrainGenerator::getMaxBuildHeight(int32_t type) {
	if(type == TERRAIN_GENERATOR_RD_132211) return RD132211::DEPTH;
	return 128;
}
