#pragma once
#include "../../../External/nlohmann/json.hpp"


class MiyaJison
{
	class Loader;
	class JsonDataLibrary;


	using Group_Value = std::array<std::string, 2>;

public:

	static MiyaJison* Get();

	MiyaJison();

	MiyaJison(const MiyaJison&) = delete;
	MiyaJison& operator=(const MiyaJison&) = delete;
	MiyaJison(MiyaJison&&) = delete;
	MiyaJison& operator=(MiyaJison&&) = delete;


	const nlohmann::json& Load(std::string fileName);

protected:


private:

	std::unique_ptr<JsonDataLibrary> jsonDataLibrary;

	nlohmann::json LoadJsonFile(std::string filePath_);

};

