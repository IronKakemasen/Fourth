#include "PreCompileHeader.h"
#include "ShaderLibrary.h"
#include "../ShaderCompiler/ShaderCompiler.h"

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
    auto const shaderRegistryFilePath_MS = "Assets/Registry/MSFiles.txt";
    auto const shaderRegistryFilePath_PS = "Assets/Registry/PSFiles.txt";

    std::unordered_map<std::string, std::string> shaderRegistryMS;
    std::unordered_map<std::string, std::string> shaderRegistryPS;

    shaderRegistryMS = LoadShaderRegistry(shaderRegistryFilePath_MS);
    shaderRegistryPS = LoadShaderRegistry(shaderRegistryFilePath_PS);
    Logger::Log("Complete Loading ShaderRegistryFile");

    for (const auto& [key, value] : shaderRegistryMS)
    {
        data[key] = compiler_->CompileShader(value, key, msProfile);
    }

    for (const auto& [key, value] : shaderRegistryPS)
    {
        data[key] = compiler_->CompileShader(value, key, psProfile);
    }
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string, std::string> ShaderLibrary::LoadShaderRegistry(const std::string& filePath) 
{
    std::unordered_map<std::string, std::string> registry;

    std::ifstream file(filePath);
    ErrorMessageOutput::Abort::DetectError(file.is_open(), "Registryフォルダの中のファイルが読み込めない", fileName);

    std::regex pattern("key:\\s*\"([^\"]*)\"\\s*,\\s*value:\\s*\"([^\"]*)\"");
    std::string line;
    std::smatch match;

    while (std::getline(file, line)) 
    {
        if (std::regex_search(line, match, pattern)) 
        {
            std::string key = match[1].str();
            std::string value = match[2].str();

            registry[key] = value;
        }
    }

    file.close();
    return registry;
}