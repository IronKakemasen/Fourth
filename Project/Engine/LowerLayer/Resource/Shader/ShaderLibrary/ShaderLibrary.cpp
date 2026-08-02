#include "ShaderLibrary.h"
#include "../ShaderCompiler/ShaderCompiler.h"
#include "RegistryLoader/RegistryLoader.h"
#include "StringConverter/StringConverter.h"

#include <regex>
#include <iostream>

namespace
{
    std::string const fileName = "ShaderLibrary.cpp";
}

ShaderLibrary::ShaderLibrary(InstanceKey key_, ShaderContext::Compiler* compiler_)
{
    Logger::Entry("ShaderLibrary: Constructor");

    CompileAllShaderFiles(compiler_);

    Logger::End("ShaderLibrary: Constructor");

}

///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
IDxcBlob* ShaderLibrary::Export(GetDataKey key_, const std::string& fileName_)
{   
    ErrorMessageOutput::Assert::DetectError
    (
        data.find(fileName_) != data.end(),
        fileName_ + "このキーがそもそも存在しない", 
        fileName
    );

    ErrorMessageOutput::Assert::DetectError
    (
        data.at(fileName_),
        fileName_ + "このキーの中身がない",
        fileName
    );

    return data.at(fileName_).Get();
}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
void ShaderLibrary::CompileAllShaderFiles(ShaderContext::Compiler* compiler_)
{
    auto const psProfile = L"ps_6_6";
    auto const msProfile = L"ms_6_6";

    std::string const shaderArgmentJsonPath = "Assets/JsonFiles/EngineCoreJsonFile/";

    std::unordered_map<std::string, std::string> shaderRegistryMS = 
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kMSFiles>();

    std::unordered_map<std::string, std::string> shaderRegistryPS = 
        RegistryLoader::Load<RegistryLoader::RegistryFileType::kPSFiles>();

    //シェーダのargmentsが詰まってる
    auto shaderFileNameToArgs = GetArgs();

    for (const auto& [key, value] : shaderRegistryMS)
    {
        data[key] = compiler_->CompileShader(value, key, msProfile, shaderFileNameToArgs[key]);
    }

    for (const auto& [key, value] : shaderRegistryPS)
    {
        data[key] = compiler_->CompileShader(value, key, psProfile, shaderFileNameToArgs[key]);
    }
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string, std::vector<std::wstring>> ShaderLibrary::GetArgs()
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

    auto* miyaJison = MiyaJison::Get();

    //シェーダーのセッティングが記述されているジェーソンファイルのキー
    auto const srcJsonFileKey = "ShaderSettings";
    std::unordered_map<std::string, std::vector<std::string>> argsMap;

    for (auto const& key : allShaderFileNames)
    {
        auto const groupName = key;

        std::vector<std::string> args =
            miyaJison->LoadData<std::vector<std::string>>(srcJsonFileKey, { groupName ,"Args" });

        argsMap[key] = args;
    }

    for (auto [key,value] : argsMap)
    {
        for (auto& arg : value)
        {
            shaderArgs[key].emplace_back(StringConverter::ConvertString(arg));
        }
    }

    return shaderArgs;
}