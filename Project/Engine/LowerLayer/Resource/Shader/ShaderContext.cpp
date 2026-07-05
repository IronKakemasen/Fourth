
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

	shaderLibrary.reset(new ShaderLibrary(ShaderLibrary::InstanceKey{}, compiler.get()));
	Logger::Log("Instantiate: ShaderLibrary", fileName);


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
