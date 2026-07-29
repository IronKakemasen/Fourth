#include "ShaderLibrary.h"
#include "../ShaderCompiler/ShaderCompiler.h"
#include "LoadRegistry/LoadRegistry.h"

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
    std::string const shaderRegistryFilePath_MS = "Assets/Registry/MSFiles.txt";
    std::string const shaderRegistryFilePath_PS = "Assets/Registry/PSFiles.txt";

    std::unordered_map<std::string, std::string> shaderRegistryMS;
    std::unordered_map<std::string, std::string> shaderRegistryPS;

    shaderRegistryMS = LoadRegistry::Load(shaderRegistryFilePath_MS);
    Logger::Log("Load: " + shaderRegistryFilePath_MS, fileName);
    shaderRegistryPS = LoadRegistry::Load(shaderRegistryFilePath_PS);
    Logger::Log("Load: " + shaderRegistryFilePath_PS, fileName);

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
