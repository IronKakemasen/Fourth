#include "PreCompileHeader.h"
#include "TextureBufferCreator.h"
#include "../BufferCreator.h"
#include "../BufferCollector/BufferCollector.h"
#include "../BufferUploader/BufferUploader.h"
#include "TextureDataLoader/TextureDataLoader.h"
#include "TextureFileLoader/TextureFileLoader.h"
#include "../../BufferDefinition/BufferDescriptions/Texture2DBufferDescription/Texture2DBufferDescription.h"

//外部
#include "RegistryLoader/RegistryLoader.h"


BufferContext::TextureBufferCreator::TextureBufferCreator
(
	NexusFieldProof proof_,
	BufferCreator& bufferCreator_,
	BufferUploader& bufferUploader_,
	GlobalConstantBufferCreator& globalConstantBufferCreator_,
	TextureBufferLibrary& textureBufferLibrary_
)
{
	///目標
	//全てのテクスチャファイルを読み込み、バッファを作成してlibraryにつめていく。
	//全バッファのsrvをひとまとまりにしたものをStaticStructuredBufferとして作成し、アップロード
	//そのバッファのsrvIndexをさらにGlobalConstantBufferで送る

	Logger::Log("- - - - Create All TextureBuffer - - - -","TextureBufferCreator.cpp\n");

	struct DescEntry
	{
		DirectX::ScratchImage scratchImage;
		Texture2DState texture2DState;
	};
	
	std::map<std::string, DescEntry> descEntries;

	//Registryに登録されているテクスチャファイルのキーを走査する
	auto const allKey_values = RegistryLoader::Load<RegistryLoader::RegistryFileType::kTextureFiles>();

	for (auto const&[ key,value ]: allKey_values)
	{
		//まずテクスチャファイルのジェーソンファイルからデータを読む
		descEntries[key].texture2DState = TextureDataLoader::LoadTextureState(key);

		//DirectTex様を利用してファイルを読み込み、DirectX::ScratchImageを取得
		descEntries[key].scratchImage = TextureFileLoader::LoadTextureFile(value, descEntries[key].texture2DState.type);
	}






}
