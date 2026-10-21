#pragma once
#include <item/ItemInstance.hpp>

struct CraftingContainer
{
	struct _cc_unknown
	{
		virtual void empty();
		virtual void empty2();
		virtual ItemInstance* doSomething(int);
	};
	_cc_unknown* field_0; //TODO find out what is field_0 - doesnt seem to be referenced anywhere
	int field_4, field_8, field_C, field_10, field_14;
	ItemInstance* getItem(int32_t a2, int32_t a3) {
		if(a2 < 0) return 0;
		int f14 = this->field_14;
		if(a2 >= f14) return 0;
		return this->field_0->doSomething(a3*f14 + a2);
	}
};
