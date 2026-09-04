#pragma once
#include "../Miyajison.h"
#include "../JsonDataChecker/JsonDataChecker.h"

class Miyajison::DataLoader
{
	friend class Miyajison;

	template<typename DataType>
	static DataType Load(const nlohmann::json& jsonData, Group_Value group_value_)
	{
		//データ型チェック
		Miyajison::DataChecker::Check<DataType>();

		auto data = jsonData[group_value_[0]][group_value_[1]];
		auto value = data.get<DataType>();

		return value;
	}

};

