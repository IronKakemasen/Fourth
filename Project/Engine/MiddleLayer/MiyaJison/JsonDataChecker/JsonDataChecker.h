#pragma once
#include "../MiyaJison.h"


class MiyaJison::DataChecker
{
	friend class MiyaJison;

	///ProjectConfigのテータチェックフラグがオンの時に作動する
	template<typename DataType>
	static void Check()
	{
		if (!ProjectConfig::Debug::kEnableJsonDataTypeCheck) return;

		if constexpr
		(
			!std::is_same_v<DataType, std::string>   &&
			!std::is_same_v<DataType, int>			 &&
			!std::is_same_v<DataType, bool>			 &&
			!std::is_same_v<DataType, double>
		)
		{
			ErrorMessageOutput::Assert::OutputError("データ型に異常あり", "JsonDataLoader.h");
		}
	}

};

