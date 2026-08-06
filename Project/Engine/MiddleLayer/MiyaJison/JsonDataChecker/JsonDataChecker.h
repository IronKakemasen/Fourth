#pragma once
#include "../Miyajison.h"


class Miyajison::DataChecker
{
	friend class Miyajison;

	///ProjectConfigのテータチェックフラグがオンの時に作動する
	template<typename DataType>
	static void Check()
	{
		if (!ProjectConfig::Debug::kEnableJsonDataTypeCheck) return;

		if constexpr
		(
			!std::is_same_v<DataType, std::string>					&&
			!std::is_same_v<DataType, int>							&&
			!std::is_same_v<DataType, bool>							&&
			!std::is_same_v<DataType, double>						&&
			!std::is_same_v<DataType, std::vector<std::string>>		&&
			!std::is_same_v<DataType, std::vector<int>>				&&
			!std::is_same_v<DataType, std::vector<bool>>			&&
			!std::is_same_v<DataType, std::vector<double>>

		)
		{
			ErrorMessageOutput::Assert::OutputError("データ型に異常あり", "JsonDataLoader.h");
		}
	}

};

