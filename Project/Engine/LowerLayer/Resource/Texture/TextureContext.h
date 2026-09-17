#pragma once

class Nexus;
class BufferContextDiplomat;
class TextureContextDiplomat;

class TextureContext
{
	//全てのテクスチャファイルを読み込み、バッファを作成する
	//そしてlibraryにつめていく。そしてsrvをひとまとまりにしたものをstructuredBufferとして作成し、アップロード
	//そのバッファのsrvIndexをさらにGlobalConstantBufferで送るまでやる
	class TextureBufferCreator;

public:

	///テクスチャファイル名をキーとしてsrvHeapIndexを管理する
	class TextureLibrary;
	class ToolLender;


	//ネクサスフィールドの証
	struct NexusFieldProof;

	TextureContext
	(
		NexusFieldProof proof_, 
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~TextureContext();

	std::unique_ptr<TextureContextDiplomat> diplomat;

private:

	std::unique_ptr<TextureLibrary> textureLibrary;

};


struct TextureContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

