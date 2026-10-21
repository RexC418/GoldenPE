#include <gui/buttons/TerrainSelectorButton.hpp>
#include <Minecraft.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <unigl.hpp>

//The triangles are in gui/terrain_arrows.png (256 x 256): the one pointing left at 0, 0 and the one pointing right at 16, 0
enum {
	ARROW_WIDTH = 13,
	ARROW_HEIGHT = 14,
	ARROW_RIGHT_U = 16
};

TerrainSelectorArrowButton::TerrainSelectorArrowButton(int32_t id, bool_t pointsRight) : Touch::TButton(id, "", 0) {
	this->pointsRight = pointsRight;
}

void TerrainSelectorArrowButton::renderFace(struct Minecraft* mc, int32_t mouseX, int32_t mouseY) {
	//Same colors and pressed offset that the text of the buttons has
	bool_t down = this->active && this->pressed && this->isInside(mouseX, mouseY);
	uint32_t rgb = 0xE0E0E0;
	if(!this->active) rgb = 0xA0A0A0;
	else if(down) rgb = 0xFFFFA0;
	uint32_t shadow = (rgb & 0xFCFCFC) >> 2;

	if(!mc->texturesPtr->loadAndBindTexture("gui/terrain_arrows.png")) return;

	//Centered by the weight of the triangle (its base), not by its bounding box, so it looks centered in the button
	int32_t x = this->posX + (this->width - ARROW_WIDTH) / 2 + (this->pointsRight ? 2 : -1) + (down ? 1 : 0);
	int32_t y = this->posY + (this->height - ARROW_HEIGHT) / 2 + (down ? 1 : 0);
	float u0 = (this->pointsRight ? ARROW_RIGHT_U : 0) / 256.0f;
	float u1 = u0 + ARROW_WIDTH / 256.0f;
	float v1 = ARROW_HEIGHT / 256.0f;

	glColor4f(1, 1, 1, 1);
	for(int32_t pass = 0; pass < 2; ++pass) { //first the shadow, then the triangle
		float dx = (float)(x + (pass == 0 ? 1 : 0));
		float dy = (float)(y + (pass == 0 ? 1 : 0));
		Tesselator::instance.begin(4);
		Tesselator::instance.color(0xFF000000 | (pass == 0 ? shadow : rgb));
		Tesselator::instance.vertexUV(dx, dy, this->zLayer, u0, 0);
		Tesselator::instance.vertexUV(dx, dy + ARROW_HEIGHT, this->zLayer, u0, v1);
		Tesselator::instance.vertexUV(dx + ARROW_WIDTH, dy + ARROW_HEIGHT, this->zLayer, u1, v1);
		Tesselator::instance.vertexUV(dx + ARROW_WIDTH, dy, this->zLayer, u1, 0);
		Tesselator::instance.draw(1);
	}
}

TerrainSelectorNameButton::TerrainSelectorNameButton(int32_t id, const std::string& name) : Touch::TButton(id, name, 0) {
}
