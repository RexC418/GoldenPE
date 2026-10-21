#pragma once
#include <_types.h>
#include <string>
#include <gui/screens/PlayScreenStateSetting.hpp>
#include <gui/screens/PlayScreenPanel.hpp>

struct PlayScreenStateSetting
{
	bool_t showEditButton, field_1, field_2, field_3;
	bool_t showNewButton, showExternalButton;
	int8_t field_6, field_7;
	PlayScreenPanel panel;
	std::string field_C;

	PlayScreenStateSetting() {
		this->field_C = "";
		this->showEditButton = 0;
		this->field_1 = 0;
		this->field_2 = 0;
		this->field_3 = 0;
		this->showExternalButton = 0;
		this->showNewButton = 0;
		this->panel = PlayScreenPanel::NONE;
	}
	PlayScreenStateSetting(bool_t a3, bool_t a4, bool_t a5, bool_t a6, bool_t a7, bool_t a8, PlayScreenPanel a9) {
		this->field_C = "";
		this->showEditButton = a3;
		this->field_1 = a4;
		this->field_2 = a5;
		this->field_3 = a6;
		this->showExternalButton = a7;
		this->showNewButton = a8;
		this->panel = a9;
	}

};
