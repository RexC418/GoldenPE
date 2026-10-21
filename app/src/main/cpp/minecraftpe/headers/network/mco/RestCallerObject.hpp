#pragma once
#include <network/mco/RestCallerInterup.hpp>
#include <network/mco/RestCallTagData.hpp>
#include <network/mco/MCOConnector.hpp>
#include <network/mco/RestCallerType.hpp>

struct RestCallerObject
{
	RestCallerInterup interup;
	struct RestCaller* restCaller;
	RestCallerType type;
	std::string field_C, field_10;
	void (MCOConnector::*field_14)(int32_t, std::string, const RestCallTagData&);
	void (MCOConnector::*field_1C)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&);
	int field_24;
	RestCallTagData field_28;
	int field_34;

	RestCallerObject(RestCallerType t, RestCallerInterup i, RestCaller* rc, const char_t* a4, const char_t* a5, void (MCOConnector::*a6)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*a7)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a8, int32_t a9)
		: interup(i)
		, type(t) {
		this->field_C = a4;
		this->restCaller = rc;
		this->field_14 = a6;
		this->field_1C = a7;
		this->field_28 = a8;
		this->field_24 = a9;
		if(a5) this->field_10 = a5;
	}
};
