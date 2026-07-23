#pragma once

class Nexus;
class ShaderLibrary;
class PSO_Context;

class ShaderContext
{
public:

	//ネクサスフィールドの証
	struct NexusFieldProof;
	//シェーダーライブラリを貸し出し許可キー
	struct ShaderLibraryAccessKey;
	//コンパイラー
	class Compiler;

	//シェーダーライブラリを貸し出し
	ShaderLibrary* AllowAccessToLibrary(ShaderLibraryAccessKey accessKey_);
	
	ShaderContext(NexusFieldProof proof_);
	~ShaderContext();

private:

	std::unique_ptr<Compiler> compiler;
	//シェーダーのデータがすべてここに
	std::unique_ptr<ShaderLibrary> shaderLibrary;
};


struct ShaderContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct ShaderContext::ShaderLibraryAccessKey
{
private:

	friend class PSO_Context;
	explicit ShaderLibraryAccessKey() = default;
};

