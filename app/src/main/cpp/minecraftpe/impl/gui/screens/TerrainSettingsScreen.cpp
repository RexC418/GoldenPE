#include <gui/screens/TerrainSettingsScreen.hpp>
#include <Minecraft.hpp>
#include <cpputils.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/buttons/TerrainSelectorButton.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <gui/elements/Label.hpp>
#include <gui/screens/CreateWorldScreen.hpp>
#include <level/gen/TerrainGenerator.hpp>
#include <rendering/Tesselator.hpp>
#include <util/IntRectangle.hpp>

CreateWorldScreenState TerrainSettingsScreen::pendingCreateWorldState;

TerrainSettingsScreen::TerrainSettingsScreen(CreateWorldScreenType type, const MCOServerListItem& item)
	: Screen() {
	this->header = 0;
	this->backButton = 0;
	this->leftButton = 0;
	this->rightButton = 0;
	this->nameButton = 0;
	this->titleLabel = 0;
	this->panel = 0;
	this->panelY = 0;
	this->createWorldType = type;
	this->createWorldItem = item;
}
TerrainSettingsScreen::~TerrainSettingsScreen() {
	safeRemove<Button>(this->header);
	safeRemove<Button>(this->backButton);
	safeRemove<Button>(this->leftButton);
	safeRemove<Button>(this->rightButton);
	safeRemove<Button>(this->nameButton);
	safeRemove<Label>(this->titleLabel);
	safeRemove<NinePatchLayer>(this->panel);
}
void TerrainSettingsScreen::closeScreen() {
	//Back to the Create World screen, which restores what was typed in it
	this->minecraft->setScreen(new CreateWorldScreen(this->createWorldType, this->createWorldItem));
}
void TerrainSettingsScreen::changeGenerator(int32_t direction) {
	//With only one generator there is nothing to switch to, so the buttons do nothing
	if(TerrainGenerator::getSelectableCount() <= 1) return;
	TerrainGenerator::setSelectedIndex(TerrainGenerator::getSelectedIndex() + direction);
	this->nameButton->setMsg(TerrainGenerator::getVersionName(TerrainGenerator::getSelectedType()));
}
void TerrainSettingsScreen::init() {
	this->header = new Touch::THeader(0, "Terrain Settings");

	this->backButton = new Touch::TButton(1, "Back", 0);
	this->backButton->width = 38;
	this->backButton->height = 18;
	((Touch::TButton*)this->backButton)->init(this->minecraft);

	//[ < ][ name of the version ][ > ]: three original buttons one next to the other
	this->leftButton = new TerrainSelectorArrowButton(2, 0);
	this->rightButton = new TerrainSelectorArrowButton(3, 1);
	this->nameButton = new TerrainSelectorNameButton(4, TerrainGenerator::getVersionName(TerrainGenerator::getSelectedType()));
	((Touch::TButton*)this->leftButton)->init(this->minecraft, "gui/spritesheet.png", {8, 32, 8, 8}, {0, 32, 8, 8}, 2, 2, SELECTOR_HEIGHT, SELECTOR_HEIGHT);
	((Touch::TButton*)this->rightButton)->init(this->minecraft, "gui/spritesheet.png", {8, 32, 8, 8}, {0, 32, 8, 8}, 2, 2, SELECTOR_HEIGHT, SELECTOR_HEIGHT);
	((Touch::TButton*)this->nameButton)->init(this->minecraft, "gui/spritesheet.png", {8, 32, 8, 8}, {0, 32, 8, 8}, 2, 2, 100, SELECTOR_HEIGHT);

	this->titleLabel = new Label("Terrain Generation", this->minecraft, -1, 0, 0, 0, 1);

	NinePatchFactory factory(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->panel = factory.createSymmetrical({34, 43, 14, 14}, 3, 3, 32, 32);

	this->buttons.push_back(this->header);
	this->buttons.push_back(this->backButton);
	this->buttons.push_back(this->leftButton);
	this->buttons.push_back(this->nameButton);
	this->buttons.push_back(this->rightButton);
	this->field_2C.push_back(this->backButton);
	this->field_2C.push_back(this->leftButton);
	this->field_2C.push_back(this->rightButton);
}
void TerrainSettingsScreen::setupPositions() {
	this->backButton->posX = 4;
	this->backButton->posY = 4;
	this->header->posX = 0;
	this->header->posY = 0;
	this->header->width = this->width;
	this->header->height = this->backButton->height + 8;

	int32_t nameWidth = this->width / 3;
	if(nameWidth < 90) nameWidth = 90;
	if(nameWidth > 140) nameWidth = 140;
	this->leftButton->width = SELECTOR_HEIGHT;
	this->rightButton->width = SELECTOR_HEIGHT;
	this->nameButton->width = nameWidth;

	int32_t panelTop = this->header->height + 8;
	this->titleLabel->posY = panelTop + 10;
	this->titleLabel->posX = this->width / 2 - this->titleLabel->width / 2;

	//The three parts are one next to the other, with no gap, and centered
	int32_t selectorWidth = SELECTOR_HEIGHT + nameWidth + SELECTOR_HEIGHT;
	int32_t selectorX = this->width / 2 - selectorWidth / 2;
	int32_t selectorY = this->titleLabel->posY + 14;
	this->leftButton->posX = selectorX;
	this->nameButton->posX = selectorX + SELECTOR_HEIGHT;
	this->rightButton->posX = selectorX + SELECTOR_HEIGHT + nameWidth;
	this->leftButton->posY = selectorY;
	this->nameButton->posY = selectorY;
	this->rightButton->posY = selectorY;
	this->leftButton->height = SELECTOR_HEIGHT;
	this->nameButton->height = SELECTOR_HEIGHT;
	this->rightButton->height = SELECTOR_HEIGHT;

	this->panelY = panelTop;
	this->panel->setSize((float)this->width - 10.0f, (float)(selectorY + SELECTOR_HEIGHT + 10 - panelTop));
}
void TerrainSettingsScreen::render(int32_t x, int32_t y, float partialTicks) {
	this->renderMenuBackground(partialTicks);
	this->panel->draw(Tesselator::instance, 5.0f, (float)this->panelY);
	this->titleLabel->render(this->minecraft, x, y);
	Screen::render(x, y, partialTicks);
}
bool_t TerrainSettingsScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->closeScreen();
	}
	return 1;
}
void TerrainSettingsScreen::buttonClicked(Button* button) {
	if(button == this->backButton) {
		this->closeScreen();
	} else if(button == this->leftButton) {
		this->changeGenerator(-1);
	} else if(button == this->rightButton) {
		this->changeGenerator(1);
	}
}
