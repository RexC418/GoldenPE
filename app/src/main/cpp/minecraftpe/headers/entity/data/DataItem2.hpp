#pragma once
#include <entity/data/DataItem.hpp>
#include <string>
#include <item/ItemInstance.hpp>
#include <math/Pos.hpp>

template<typename T>
struct DataType{
	static const int typeId;
};
template<>
struct DataType<int8_t>{
	static const int typeId = 0;
};
template<>
struct DataType<int16_t>{
	static const int typeId = 1;
};
template<>
struct DataType<int32_t>{
	static const int typeId = 2;
};
template<>
struct DataType<float>{
	static const int typeId = 3;
};
template<>
struct DataType<std::string>{
	static const int typeId = 4;
};
template<>
struct DataType<ItemInstance>{
	static const int typeId = 5;
};
template<>
struct DataType<Pos>{
	static const int typeId = 6;
};

template<typename T>
struct DataItem2: DataItem
{
	T value;

	DataItem2(int32_t id, T v) {
		this->typeId = DataType<T>::typeId;
		this->value = v;
		this->dirty = 1;
	}
	virtual ~DataItem2() {
	}
};
