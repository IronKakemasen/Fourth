#include "ShaderContext.h"
#include "ShaderLibrary/ShaderLibrary.h"
#include "ShaderLoader/ShaderLoader.h"
#include "ShaderContextDiplomat/ShaderContextDiplomat.h"
#include "ShaderContextDiplomat/ShaderContextToolLender/ShaderContextToolLender.h"



namespace
{
	auto fileName = "ShaderContext.cpp";
}


ShaderContext::ShaderContext(NexusFieldProof proof_)
{
	Logger::Entry("ShaderContext: Constructor");


	shaderLibrary.reset(new ShaderLibrary(proof_));
	Logger::Log("Instantiate: ShaderLibrary", fileName);

	//全てのシェーダーファイルを読み込み、コンパイルしてライブラリーにぶっこむ
	ShaderLoader shaderLoader(proof_, shaderLibrary.get());

	diplomat.reset
	(
		new ShaderContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, shaderLibrary.get())
		)
	);


	Logger::End("ShaderContext: Constructor");
}

ShaderContext::~ShaderContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
