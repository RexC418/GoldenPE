#pragma once
#include <gui/Screen.hpp>
#include <gui/screens/CreateWorldScreenType.hpp>
#include <network/mco/MCOServerListItem.hpp>
#include <string>

struct NinePatchLayer;
struct Label;

//What was typed in the Create World screen. That screen is destroyed when this one opens (the Minecraft class owns
//the current screen only), so it is kept here until the Create World screen is created again to restore it.
struct CreateWorldScreenState{
	bool_t saved;
	std::string worldName;
	std::string seed;
	bool_t creative;

	CreateWorldScreenState() : saved(0), creative(1) {
	}
};

//"Terrain Settings" screen: all the settings related to the terrain of the world that is going to be created.
//It is opened from the Create World screen.
struct TerrainSettingsScreen : Screen{
	enum {
		SELECTOR_HEIGHT = 26
	};
	static CreateWorldScreenState pendingCreateWorldState;

	Button* header;
	Button* backButton;
	Button* leftButton;	 //previous generator
	Button* rightButton; //next generator
	Button* nameButton;	 //name of the version of the selected generator
	Label* titleLabel;
	NinePatchLayer* panel;
	int32_t panelY;
	CreateWorldScreenType createWorldType;
	MCOServerListItem createWorldItem;

	TerrainSettingsScreen(CreateWorldScreenType, const MCOServerListItem&);
	void closeScreen();
	void changeGenerator(int32_t direction);

	virtual ~TerrainSettingsScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void buttonClicked(Button*);
};
