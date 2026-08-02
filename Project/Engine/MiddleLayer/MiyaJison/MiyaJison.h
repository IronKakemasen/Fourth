#pragma once
#include "../../../External/nlohmann/json.hpp"

class MiyaJison
{
	class DataLoader;
	class DataLibrary;
	class DataChecker;

public:

	using Group_Value = std::array<std::string, 2>;

	static MiyaJison* Get();

	MiyaJison();

	MiyaJison(const MiyaJison&) = delete;
	MiyaJison& operator=(const MiyaJison&) = delete;
	MiyaJison(MiyaJison&&) = delete;
	MiyaJison& operator=(MiyaJison&&) = delete;

	///ジェーソンファイル名(「.json」省略！！！！)、グループ名とキーを入力し目的のデータを引っ張る
	///ファイル名はすべてAssets/Registryにあるからそこを見るべし
	template<typename DataType>
	DataType LoadData(std::string fileName_, Group_Value group_value_);


private:

	std::unique_ptr<DataLibrary> jsonDataLibrary;

	///ファイル名からジェーソンデータをライブラリーから引っ張り、返す
	const nlohmann::json& PullJsonData(std::string fileName_);

	//パスからジェーソンファイルを読み込んでジェーソンデータを返す
	nlohmann::json LoadJsonFile(std::string filePath_);

	//ジェーソンファイルレジストリーから全てのジェーソンファイルのパスを取得して読み込み、
	///ライブラリーに詰めていく
	void LoadAllJsonFiles();
};

template<>
int MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
double MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
bool MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::string MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<int> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<double> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<bool> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<std::string> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_);
