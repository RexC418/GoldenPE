#pragma once
#include <gui/buttons/Touch_TButton.hpp>
#include <string>

//The two side buttons of the "Terrain Generation" selector: a Touch::TButton with a solid triangle drawn over it
struct TerrainSelectorArrowButton : Touch::TButton{
	bool_t pointsRight;

	TerrainSelectorArrowButton(int32_t id, bool_t pointsRight);

	virtual ~TerrainSelectorArrowButton() {
	}
	virtual void renderFace(struct Minecraft*, int32_t, int32_t);
};

//The middle part of the selector. It only shows the name of the version, so it can't be pressed
struct TerrainSelectorNameButton : Touch::TButton{
	TerrainSelectorNameButton(int32_t id, const std::string& name);

	virtual ~TerrainSelectorNameButton() {
	}
	virtual bool_t clicked(struct Minecraft*, int32_t, int32_t) {
		return 0;
	}
};
