#pragma once
#include "../ShaderContext.h"


class ShaderContext::ShaderLoader
{
public:

	ShaderLoader
	(
		NexusFieldProof proof_, 
		ShaderContext::ShaderLibrary* shaderLibrary_
	);

private:

	//全てのシェーダーファイルをコンパイルする
	void CompileAllShaderFiles(NexusFieldProof proof_, ShaderLibrary* shaderLibrary_);
	//シェーダファイルのArgsをjsonファイルから読み取る
	std::unordered_map<std::string, std::vector<std::wstring>> GetArgs();

};

