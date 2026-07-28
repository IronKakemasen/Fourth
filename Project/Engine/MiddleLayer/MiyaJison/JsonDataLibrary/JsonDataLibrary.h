#pragma once
#include "../MiyaJison.h"


class MiyaJison::JsonDataLibrary
{
public:

	struct HandleLicence;

	const nlohmann::json& Export(HandleLicence licence_, std::string fileName_)const;
	void Import(HandleLicence licence_, std::string fileName_, nlohmann::json jsonData_);


private:
	std::map<std::string, nlohmann::json> lib;

};


struct MiyaJison::JsonDataLibrary::HandleLicence
{
private:

	friend class MiyaJison;

	explicit HandleLicence() = default;
};


