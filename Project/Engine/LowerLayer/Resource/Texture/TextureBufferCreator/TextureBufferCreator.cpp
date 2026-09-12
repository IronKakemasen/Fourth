#include "PreCompileHeader.h"
#include "TextureBufferCreator.h"
#include "../TextureLibrary/TextureLibrary.h"
#include "TextureBufferAssembler/TextureBufferAssembler.h"
#include "TextureDataLoader/TextureDataLoader.h"
#include "TextureFileLoader/TextureFileLoader.h"
#include "GlobalConstantBufferPackager/GlobalConstantBufferPackager.h"


//外部
#include "../../../../../External/DirectXTex/DirectXTex.h"
#include "../../../Buffer/BufferDefinition/TextureComponent.h"
#include "RegistryLoader/RegistryLoader.h"

TextureContext::TextureBufferCreator::TextureBufferCreator
(
	NexusFieldProof proof_,
	TextureLibrary& textureLibrary_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	///目標
	//全てのテクスチャファイルを読み込み、バッファを作成してlibraryにつめていく。
	//全バッファのsrvをひとまとまりにしたものをStaticStructuredBufferとして作成し、アップロード
	//そのバッファのsrvIndexをさらにGlobalConstantBufferで送る

	Logger::Log("\n- - - - Create All TextureBuffer - - - -", "TextureBufferCreator.cpp\n");

	struct DescEntry
	{
		DirectX::ScratchImage scratchImage;
		Texture2DState texture2DState;
	};


	std::map<std::string, DescEntry> descEntries;
	std::vector<SRVHeapIndex> tmpIndices;

	//Registryに登録されているテクスチャファイルのキーを走査する
	auto const allKey_values = RegistryLoader::Load<RegistryLoader::RegistryFileType::kTextureFiles>();

	for (auto const& [key, value] : allKey_values)
	{
		//まずテクスチャファイルのジェーソンファイルからデータを読む
		descEntries[key].texture2DState = TextureDataLoader::LoadTextureState(key);

		//DirectTex様を利用してファイルを読み込み、DirectX::ScratchImageを取得
		descEntries[key].scratchImage = TextureFileLoader::LoadTextureFile(value, descEntries[key].texture2DState.type);
	}

	//Texture2DBufferDescriptionを作成し、それをもとにバッファを作成。アップロードしていく
	for (auto& [key, value] : descEntries)
	{
		//作成したテクスチャバッファのSRVHeapIndex
		SRVHeapIndex const dstIndex =
			BufferAssembler::AssembleTexture2DBuffer(key, value.scratchImage, value.texture2DState, bufferContextDiplomat_);

		//テクスチャファイル名をキーとして追加していく
		textureLibrary_.Import(proof_, key, dstIndex);
		tmpIndices.emplace_back(dstIndex);
	}

	//最後に全部のsrvHeapIndexを配列にしてそのStaticStructuredBufferを作成し、
	//そのsrvHeapIndexのGlobalConstantBufferを作成
	GlobalConstantBufferPackager::Package(tmpIndices, bufferContextDiplomat_);


	//デバッグ出力
	textureLibrary_.Log();

	Logger::Log("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -", "TextureBufferCreator.cpp");

}
