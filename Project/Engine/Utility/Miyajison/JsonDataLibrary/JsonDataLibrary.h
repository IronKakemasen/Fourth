#pragma once
#include "../Miyajison.h"


class Miyajison::DataLibrary
{
public:

	struct HandleLicence;

	nlohmann::json& Export(HandleLicence licence_, std::string const& fileName_);
	
	void Import
	(
		HandleLicence licence_, 
		std::string const& fileName_, 
		nlohmann::json const& jsonData_, 
		std::string const& filePath_
	);

	std::string const& ToPath(std::string const& fileName_);

private:
	std::map<std::string, nlohmann::json> lib;
	std::unordered_map<std::string, std::string> fileName_Path;
};


struct Miyajison::DataLibrary::HandleLicence
{
private:

	friend class Miyajison;

	explicit HandleLicence() = default;
};


