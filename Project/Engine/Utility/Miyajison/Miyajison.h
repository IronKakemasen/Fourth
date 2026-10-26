#pragma once
#include "../../../External/nlohmann/json.hpp"

class Miyajison
{
	class DataLibrary;

public:

	static Miyajison* Get();

	Miyajison(const Miyajison&) = delete;
	Miyajison& operator=(const Miyajison&) = delete;
	Miyajison(Miyajison&&) = delete;
	Miyajison& operator=(Miyajison&&) = delete;

	///ジェーソンファイル名(「.json」省略！！！！)、グループ名とキーを入力し目的のデータを引っ張る
	///ファイル名はすべてAssets/Registryにあるからそこを見るべし
	template<typename DataType>
	DataType LoadData(std::string const& fileName_, std::vector<std::string> const& nest_)
	{
		Check<DataType>(fileName_,nest_);

		nlohmann::json* current = &PullJsonData(fileName_);

		//ポインタをずらしながら階層を辿る
		for (const auto& key : nest_)
		{
			current = &(*current)[key];
		}

		return current->get<DataType>();
	}

	template<typename DataType>
	void WriteData
	(
		std::string const& fileName_,
		std::vector<std::string> const& nest_,
		DataType const& data_
	)
	{
		Check<DataType>(fileName_,nest_);

		nlohmann::json* current = &PullJsonData(fileName_);

		for (size_t i = 0; i + 1 < nest_.size(); ++i)
		{
			std::string const& key = nest_[i];

			if (!(*current)[key].is_object())
			{
				(*current)[key] = nlohmann::json::object();
			}
			current = &(*current)[key];
		}

		//最後の階層にデータを書き込む
		(*current)[nest_.back()] = data_;

		//保存リストに追加
		if (!std::ranges::contains(saveList, fileName_))
		{
			saveList.emplace_back(fileName_);
		}
	}

	//ジェーソンファイルに実際にwrittenFilePathCacheをもとに書き込んでいく
	void Save();

private:

	Miyajison();

	std::unique_ptr<DataLibrary> jsonDataLibrary;
	//データが書き込まれたファイルパスのキャッシュ
	//name_path
	std::vector<std::string> saveList;

	///ファイル名からジェーソンデータをライブラリーから引っ張り、返す
	nlohmann::json& PullJsonData(std::string const& fileName_);

	//ファイル名→ファイルパス
	std::string const& ToFilePath(std::string const& fileName_);

	//パスからジェーソンファイルを読み込んでジェーソンデータを返す
	nlohmann::json LoadJsonFile(std::string const& filePath_);

	//ジェーソンファイルレジストリーから全てのジェーソンファイルのパスを取得して読み込み、
	///ライブラリーに詰めていく
	void LoadAllJsonFiles();

	//簡易チェック
	template<typename DataType>
	void Check(std::string const& fileName_ , std::vector<std::string> const& nest_)
	{
		if (!ProjectConfig::Debug::kEnableJsonDataCheck) return;

		ErrorMessageOutput::Assert::DetectError
		(
			!nest_.empty(),
			fileName_ + "へのデータ書き込み失敗(引数のネストが空)",
			"Miyajison.h"
		);

		if constexpr
		(
			!std::is_same_v<DataType, std::string> &&
			!std::is_same_v<DataType, int> &&
			!std::is_same_v<DataType, bool> &&
			!std::is_same_v<DataType, double> &&
			!std::is_same_v<DataType, float> &&
			!std::is_same_v<DataType, std::vector<std::string>> &&
			!std::is_same_v<DataType, std::vector<int>> &&
			!std::is_same_v<DataType, std::vector<bool>> &&
			!std::is_same_v<DataType, std::vector<double>> &&
			!std::is_same_v<DataType, std::vector<std::vector<float>>>

		)
		{
			ErrorMessageOutput::Assert::OutputError("データ型に異常あり", "Miyajison.h");
		}
	}
};
