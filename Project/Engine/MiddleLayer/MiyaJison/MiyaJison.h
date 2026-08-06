#pragma once
#include "../../../External/nlohmann/json.hpp"

class Miyajison
{
	class DataLoader;
	class DataLibrary;
	class DataChecker;

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
	DataType LoadData(std::string fileName_, Group_Value group_value_);


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
};

template<>
int Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
double Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
bool Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::string Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<int> Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<double> Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<bool> Miyajison::LoadData(std::string fileName_, Group_Value group_value_);

template<>
std::vector<std::string> Miyajison::LoadData(std::string fileName_, Group_Value group_value_);
