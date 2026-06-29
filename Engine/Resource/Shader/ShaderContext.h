#pragma once

class Nexus;
class ShaderLibrary;


class ShaderContext
{
	class Compiler;

public:

	//自身のインスタンス化キー
	struct InstanceKey;

	ShaderContext(InstanceKey instanceKey_);
	~ShaderContext();

private:

	//コンパイラー
	std::unique_ptr<Compiler> compiler;
	//シェーダーのデータがすべてここに
	std::unique_ptr<ShaderLibrary> shaderLibrary;


	//全てのシェーダーをコンパイルしてライブラリーに突っ込む
	void CompileAllShaders(InstanceKey instanceKey_);
};


struct ShaderContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
