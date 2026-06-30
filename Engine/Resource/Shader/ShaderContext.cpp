#include "PreCompileHeader.h"
#include "ShaderContext.h"

#include "ShaderLibrary/ShaderLibrary.h"

//ツール
#include "ShaderCompiler/ShaderCompiler.h"


namespace
{
	auto fileName = "ShaderContext.cpp";
}


ShaderContext::ShaderContext(InstanceKey instanceKey_)
{
	Logger::Entry("ShaderContext: Constructor");

	compiler.reset(new Compiler(instanceKey_));
	Logger::Log("Instantiate: shaderCompiler", fileName);

	shaderLibrary.reset(new ShaderLibrary(ShaderLibrary::ImportKey{}));
	Logger::Log("Instantiate: ShaderLibrary", fileName);


	CompileAllShaders();

	Logger::End("ShaderContext: Constructor");
}

ShaderContext::~ShaderContext()
{

}

ShaderLibrary* ShaderContext::AllowAccessToLibrary(ShaderLibraryAccessKey accessKey_)
{
	return shaderLibrary.get();
}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderContext::CompileAllShaders()
{
	std::string const commonFolderPath = "./Assets/Shader/";
	auto const psProfile = L"ps_6_5";
	auto const msProfile = L"ms_6_5";
	ShaderLibrary::ImportKey importKey;

	shaderLibrary->Import
	(
		importKey,
		std::move(compiler->CompileShader(commonFolderPath, "Test.MS", msProfile)),
		ShaderLibrary::MS::kStatic_Basic
	);

	shaderLibrary->Import
	(
		importKey,
		std::move(compiler->CompileShader(commonFolderPath, "Test.PS", psProfile)),
		ShaderLibrary::PS::kStandard_kBasic
	);


	Logger::Log("Complete: Loading all shaders", fileName);
}
