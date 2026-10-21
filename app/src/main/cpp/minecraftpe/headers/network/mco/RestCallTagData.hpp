#pragma once
#include <_types.h>
#include <RakNetTypes.h>
#include <string>

struct RestCallTagData{
	uint64_t guid_g;
	std::string str;
	RestCallTagData()
		: RestCallTagData(0) {
	}
	RestCallTagData(uint64_t t) {
		this->guid_g = t;
	}
};
