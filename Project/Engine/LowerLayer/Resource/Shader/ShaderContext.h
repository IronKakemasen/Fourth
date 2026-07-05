#pragma once

class Nexus;
class ShaderLibrary;
class PSO_Context;

class ShaderContext
{
public:

	//自身のインスタンス化キー
	struct InstanceKey;
	//シェーダーライブラリを貸し出し許可キー
	struct ShaderLibraryAccessKey;
	//コンパイラー
	class Compiler;


	//シェーダーライブラリを貸し出し
	ShaderLibrary* AllowAccessToLibrary(ShaderLibraryAccessKey accessKey_);
	
	ShaderContext(InstanceKey instanceKey_);
	~ShaderContext();

private:

	std::unique_ptr<Compiler> compiler;
	//シェーダーのデータがすべてここに
	std::unique_ptr<ShaderLibrary> shaderLibrary;
};


struct ShaderContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

struct ShaderContext::ShaderLibraryAccessKey
{
private:

	friend class PSO_Context;
	explicit ShaderLibraryAccessKey() = default;
};

