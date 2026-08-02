#include "PreCompileHeader.h"
#include "MiyaJison.h"
#include "JsonDataLibrary/JsonDataLibrary.h"
#include "RegistryLoader/RegistryLoader.h"
#include "JsonDataLoader/JsonDataLoader.h"

MiyaJison::MiyaJison()
{
    jsonDataLibrary.reset(new DataLibrary());
    Logger::Log("Instantiate: jsonDataLibrary", "MiyaJison.cpp");

    LoadAllJsonFiles();
}

MiyaJison* MiyaJison::Get()
{
    static MiyaJison miyaJison;

    return &miyaJison;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MiyaJison::LoadAllJsonFiles()
{
    std::unordered_map<std::string, std::string> fileName_Path =
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kJsonFiles>();

    DataLibrary::HandleLicence licence;

    for (const auto& [key, value] : fileName_Path)
    {
        jsonDataLibrary->Import(licence, key, LoadJsonFile(value));
    }
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nlohmann::json MiyaJison::LoadJsonFile(std::string filePath_)
{
    std::ifstream file(filePath_);

    ErrorMessageOutput::Abort::DetectError
    (
        file.is_open(),
        filePath_ + "こんなファイルはねぇよ！他所をあたりな",
        "Json.cpp"
    );

    nlohmann::json jsonData;
    file >> jsonData;

    return jsonData;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const nlohmann::json& MiyaJison::PullJsonData(std::string fileName_)
{
    return jsonDataLibrary->Export(DataLibrary::HandleLicence{}, fileName_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
int MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<int>(jsonData, group_value_);
}

template<>
double MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<double>(jsonData, group_value_);

}

template<>
bool MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<bool>(jsonData, group_value_);

}

template<>
std::string MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::string>(jsonData, group_value_);

}

template<>
std::vector<int> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<int>>(jsonData, group_value_);
}

template<>
std::vector<double> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<double>>(jsonData, group_value_);
}

template<>
std::vector<bool> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<bool>>(jsonData, group_value_);
}

template<>
std::vector<std::string> MiyaJison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<std::string>>(jsonData, group_value_);
}





