#pragma once

class Nexus;
class ShaderContextDiplomat;


class ShaderContext
{
public:

	//ネクサスフィールドの証
	struct NexusFieldProof;
	//シェーダーライブラリを貸し出し許可キー
	struct ShaderLibraryAccessKey;
	class ShaderLibrary;
	//ツール貸し出し
	class ToolLender;


	
	ShaderContext(NexusFieldProof proof_);
	~ShaderContext();


	std::unique_ptr<ShaderContextDiplomat> diplomat;

private:

	//コンパイラー
	class Compiler;
	//シェーダーファイルをロードする
	class ShaderLoader;


	//シェーダーのデータがすべてここに
	std::unique_ptr<ShaderLibrary> shaderLibrary;
};


struct ShaderContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

