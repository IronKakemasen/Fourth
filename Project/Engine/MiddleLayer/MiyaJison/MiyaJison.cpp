#include "PreCompileHeader.h"
#include "MiyaJison.h"
#include "JsonDataLibrary/JsonDataLibrary.h"
#include "LoadRegistry/LoadRegistry.h"

MiyaJison::MiyaJison()
{
    std::unordered_map<std::string, std::string> fileName_Path =
        LoadRegistry::Load("Assets/Registry/JsonFiles.txt");

}

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


const nlohmann::json& MiyaJison::Load(std::string fileName)
{
    return jsonDataLibrary->Export(JsonDataLibrary::HandleLicence{}, fileName);
}


MiyaJison* MiyaJison::Get()
{
    static MiyaJison miyaJison;

    return &miyaJison;
}

