#pragma once
#include "../Miyajison.h"


class Miyajison::DataLibrary
{
public:

	struct HandleLicence;

	const nlohmann::json& Export(HandleLicence licence_, std::string const& fileName_)const;
	void Import(HandleLicence licence_, std::string const& fileName_, nlohmann::json const& jsonData_);


private:
	std::map<std::string, nlohmann::json> lib;

};


struct Miyajison::DataLibrary::HandleLicence
{
private:

	friend class Miyajison;

	explicit HandleLicence() = default;
};


