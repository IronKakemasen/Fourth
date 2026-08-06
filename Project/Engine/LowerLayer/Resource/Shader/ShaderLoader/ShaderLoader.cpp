#include "PreCompileHeader.h"
#include "ShaderLoader.h"
#include "ShaderCompiler/ShaderCompiler.h"
#include "../ShaderLibrary/ShaderLibrary.h"
#include "StringConverter/StringConverter.h"
#include "RegistryLoader/RegistryLoader.h"



ShaderContext::ShaderLoader::ShaderLoader
(
	NexusFieldProof proof_,
	ShaderLibrary* shaderLibrary_
)
{
    CompileAllShaderFiles(proof_, shaderLibrary_);
}


void ShaderContext::ShaderLoader::CompileAllShaderFiles(NexusFieldProof proof_, ShaderLibrary* shaderLibrary_)
{
    ShaderContext::Compiler compiler(proof_);

    //シェーダーモデル
    auto const psProfile = L"ps_6_6";
    auto const msProfile = L"ms_6_6";

    //メッシュシェーダーファイル名とそのパスが登録されているファイル
    std::unordered_map<std::string, std::string> shaderRegistryMS =
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kMSFiles>();
    //そのピクセルシェーダーバージョン
    std::unordered_map<std::string, std::string> shaderRegistryPS =
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kPSFiles>();

    //シェーダのargmentsが詰まってる
    auto shaderFileNameToArgs = GetArgs();

    for (const auto& [key, value] : shaderRegistryMS)
    {
        shaderLibrary_->Import(proof_, key, compiler.CompileShader(value, key, msProfile, shaderFileNameToArgs[key]));
    }

    for (const auto& [key, value] : shaderRegistryPS)
    {
        shaderLibrary_->Import(proof_, key, compiler.CompileShader(value, key, psProfile, shaderFileNameToArgs[key]));
    }

    Logger::Log("Complete Load All Shaders", "ShaderLoader.cpp");
}

std::unordered_map<std::string, std::vector<std::wstring>> ShaderContext::ShaderLoader::GetArgs()
{
    //シェーダーファイルの名前をキーとしたArgs
    std::unordered_map<std::string, std::vector<std::wstring>> shaderArgs;

    //ジェーソンファイル一覧を取得
    std::unordered_map<std::string, std::string> jsonRegistry =
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kJsonFiles>();

    //メッシュシェーダーのキーのベクター
    std::vector<std::string> msShaderFileNames =
        RegistryLoader::LoadRegistryKeys<RegistryLoader::RegistryFileType::kMSFiles>();
    //ピクセルシェーダーのキーのベクター
    std::vector<std::string> psShaderFileNames =
        RegistryLoader::LoadRegistryKeys<RegistryLoader::RegistryFileType::kPSFiles>();

    //結合
    std::vector<std::string> allShaderFileNames;
    allShaderFileNames.reserve(msShaderFileNames.size() + psShaderFileNames.size());
    allShaderFileNames.insert(allShaderFileNames.end(), msShaderFileNames.begin(), msShaderFileNames.end());
    allShaderFileNames.insert(allShaderFileNames.end(), psShaderFileNames.begin(), psShaderFileNames.end());

    auto* Miyajison = Miyajison::Get();

    //シェーダーのセッティングが記述されているジェーソンファイルのキー
    auto const srcJsonFileKey = "ShaderSettings";
    std::unordered_map<std::string, std::vector<std::string>> argsMap;

    for (auto const& key : allShaderFileNames)
    {
        auto const groupName = key;

        std::vector<std::string> args =
            Miyajison->LoadData<std::vector<std::string>>(srcJsonFileKey, { groupName ,"Args" });

        argsMap[key] = args;
    }

    //stringからwstringへ
    for (auto [key, value] : argsMap)
    {
        for (auto& arg : value)
        {
            shaderArgs[key].emplace_back(StringConverter::ConvertString(arg));
        }
    }

    return shaderArgs;

}
