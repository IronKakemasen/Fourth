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

	CompileAllShaders(instanceKey_);

	Logger::End("ShaderContext: Constructor");
}

ShaderContext::~ShaderContext()
{

}

void ShaderContext::CompileAllShaders(InstanceKey instanceKey_)
{
	compiler.reset(new Compiler(instanceKey_));
	Logger::Log("Instantiate: shaderCompiler", fileName);
	
	shaderLibrary.reset(new ShaderLibrary(ShaderLibrary::ImportKey{}));
	Logger::Log("Instantiate: ShaderLibrary", fileName);

	std::string const commonFolderPath = "./Assets/Shader/";
	auto const psProfile = L"ps_6_5";
	auto const msProfile = L"ms_6_5";
	ShaderLibrary::ImportKey importKey;


	shaderLibrary->ImportPixelShaderData
	(
		importKey,
		std::move(compiler->CompileShader(commonFolderPath, "Test.PS", psProfile)),
		ShaderKey::MaterialType::kStandard, ShaderKey::Renderpath::kStandard
	);

	shaderLibrary->ImportMeshShaderData
	(
		importKey, 
		std::move(compiler->CompileShader(commonFolderPath, "Test.MS", msProfile)),
		ShaderKey::MeshType::kStatic, ShaderKey::Renderpath::kStandard
	);


	Logger::Log("Complete: Loading all shaders", fileName);
}
