#include "PreCompileHeader.h"
#include "Miyajison.h"
#include "JsonDataLibrary/JsonDataLibrary.h"
#include "RegistryLoader/RegistryLoader.h"
#include "JsonDataLoader/JsonDataLoader.h"

Miyajison::Miyajison()
{
    jsonDataLibrary.reset(new DataLibrary());
    Logger::Log("Instantiate: jsonDataLibrary", "Miyajison.cpp");

    LoadAllJsonFiles();
}

Miyajison* Miyajison::Get()
{
    static Miyajison Miyajison;

    return &Miyajison;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Miyajison::LoadAllJsonFiles()
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
nlohmann::json Miyajison::LoadJsonFile(std::string filePath_)
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
const nlohmann::json& Miyajison::PullJsonData(std::string fileName_)
{
    return jsonDataLibrary->Export(DataLibrary::HandleLicence{}, fileName_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
int Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<int>(jsonData, group_value_);
}

template<>
double Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<double>(jsonData, group_value_);

}

template<>
bool Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<bool>(jsonData, group_value_);

}

template<>
std::string Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::string>(jsonData, group_value_);

}

template<>
float Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<float>(jsonData, group_value_);

}

template<>
std::vector<int> Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<int>>(jsonData, group_value_);
}

template<>
std::vector<double> Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<double>>(jsonData, group_value_);
}

template<>
std::vector<bool> Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<bool>>(jsonData, group_value_);
}

template<>
std::vector<std::string> Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);

    return DataLoader::Load<std::vector<std::string>>(jsonData, group_value_);
}

template<>
std::vector<std::vector<float>> Miyajison::LoadData(std::string fileName_, Group_Value group_value_)
{
    const nlohmann::json& jsonData = PullJsonData(fileName_);
    return DataLoader::Load<std::vector<std::vector<float>>>(jsonData, group_value_);
}




