#include "PreCompileHeader.h"
#include "Miyajison.h"
#include "JsonDataLibrary/JsonDataLibrary.h"
#include "RegistryLoader/RegistryLoader.h"

namespace
{
    auto const fileName = "Miyajison.cpp";
}

Miyajison::Miyajison()
{
    jsonDataLibrary.reset(new DataLibrary());
    Logger::Log("Instantiate: jsonDataLibrary", fileName);

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

    //レジストリーファイルに登録されているジェーソンファイルを読み込む
    std::unordered_map<std::string, std::string> fileName_Path =
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kJsonFiles>();

    //変更保存リストのサイズを確保しておく
    saveList.reserve(fileName_Path.size());

    DataLibrary::HandleLicence licence;

    for (const auto& [key, value] : fileName_Path)
    {
        jsonDataLibrary->Import(licence, key, LoadJsonFile(value), value);
    }
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nlohmann::json Miyajison::LoadJsonFile(std::string const& filePath_)
{
    std::ifstream file(filePath_);

    ErrorMessageOutput::Abort::DetectError
    (
        file.is_open(),
        filePath_ + "こんなファイルはねぇよ！他所をあたりな",
        fileName
    );

    nlohmann::json jsonData;
    file >> jsonData;

    return jsonData;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nlohmann::json& Miyajison::PullJsonData(std::string const& fileName_)
{
    return jsonDataLibrary->Export(DataLibrary::HandleLicence{}, fileName_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const& Miyajison::ToFilePath(std::string const& fileName_)
{
    return jsonDataLibrary->ToPath(fileName_);
}

void Miyajison::Save()
{
    for (auto const& fileName : saveList)
    {
        auto const& path = ToFilePath(fileName);
        auto& jsonRoot = PullJsonData(fileName);

        std::ofstream ofs(path);

        ErrorMessageOutput::Abort::DetectError
        (
            ofs.is_open(),
            path + "が開けない",
            "Miyajison.h"
        );

        ofs << jsonRoot.dump(4);

        ErrorMessageOutput::Abort::DetectError
        (
            ofs.good(),
            path + "への書き込みに失敗",
            "Miyajison.h"
        );
    }

    saveList.clear();
}
