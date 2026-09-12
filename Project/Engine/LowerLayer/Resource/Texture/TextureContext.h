#pragma once

class Nexus;
class BufferContextDiplomat;


class TextureContext
{
	//全てのテクスチャファイルを読み込み、バッファを作成する
	//そしてlibraryにつめていく。そしてsrvをひとまとまりにしたものをstructuredBufferとして作成し、アップロード
	//そのバッファのsrvIndexをさらにGlobalConstantBufferで送るまでやる
	class TextureBufferCreator;

public:

	///テクスチャファイル名をキーとしてsrvHeapIndexを管理する
	class TextureLibrary;
	

	//ネクサスフィールドの証
	struct NexusFieldProof;

	TextureContext
	(
		NexusFieldProof proof_, 
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~TextureContext();

private:

	std::unique_ptr<TextureLibrary> textureLibrary;

};


struct TextureContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

