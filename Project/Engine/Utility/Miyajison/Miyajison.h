#pragma once
#include "../../../External/nlohmann/json.hpp"

class Miyajison
{
	class DataLibrary;

public:

	using Group_Value = std::array<std::string, 2>;

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
		CheckDataType<DataType>();

		nlohmann::json const* current = &PullJsonData(fileName_);

		//ポインタをずらしながら階層を辿る
		for (const auto& key : nest_)
		{
			current = &(*current)[key];
		}

		return current->get<DataType>();
	}

private:

	Miyajison();

	std::unique_ptr<DataLibrary> jsonDataLibrary;

	///ファイル名からジェーソンデータをライブラリーから引っ張り、返す
	const nlohmann::json& PullJsonData(std::string fileName_);

	//パスからジェーソンファイルを読み込んでジェーソンデータを返す
	nlohmann::json LoadJsonFile(std::string filePath_);

	//ジェーソンファイルレジストリーから全てのジェーソンファイルのパスを取得して読み込み、
	///ライブラリーに詰めていく
	void LoadAllJsonFiles();

	//データ型チェック
	template<typename DataType>
	void CheckDataType()
	{
		if (!ProjectConfig::Debug::kEnableJsonDataTypeCheck) return;

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
