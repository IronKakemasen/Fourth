#pragma once

class Nexus;
class CommandContextDiplomat;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;
class BufferContextDiplomat;

class GPUBufferBehavior;
template<typename ValueType> class ClosedHashMap;

class BufferContext
{
	//生成したバッファを回収し分別する
	class BufferCollector;
	//生成したバッファの削除を担当
	class BufferDeferredReleaser;
	//BufferUniqueIDから該当のバッファのアドレスをキャストして渡す
	class BufferDispatcher;
	//生リソース生成
	class ResourceCreator;

protected:

	//リソース生成コマンド
	using CreateResourceCommand = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	)>;

	//登録先識別用
	enum class RegisterType
	{
		kRenderTarget,
		kFrameBuffer,
		kComputeBuffer,
		kReadOnlyBuffer,
		kCount
	};

	struct BufferPoolSet
	{
		BufferPoolSet();

		//ColorBufferやDepthStencilBufferなどレンダーターゲットなバッファプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> renderTargetBufferPool;
		//computeBufferのような、コンピュートシェーダをかませるバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> computeBufferPool;
		//ConstantBufferやUploadStructuredBufferのようなフレームバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> frameBufferPool;
		//staticStructuredBufferやtextureBufferのような、読みしかしない確定のシングルバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> readOnlyBufferPool;

		//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
		//std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>> bufferLocationMap;
		std::unique_ptr<ClosedHashMap<std::pair<RegisterType, uint32_t>>> bufferLocationClosedHashedMap;
		//RegisterTypeがキーのテーブル
		std::vector<std::unique_ptr<GPUBufferBehavior>>* ContainerTable(BufferContext::RegisterType type_);

	private:
		//bufferLocationClosedHashedMapのサイズ
		static constexpr int kHashedMapSize = 16384;
	};

public:

	//自身のインスタンス化キー
	struct InstanceKey;
	//バッファのポインタを扱うものの証
	struct BufferAccessKey;

	//BufferAssemblerとBufferCollectorをつかってバッファを作成する
	class BufferCreator;
	//BufferDescriptionをもとにバッファを組み立てる
	class BufferAssembler;
	//ランタイムパス構築に必要な情報の抽出とそのリソースのSwapを行う
	class BufferInfoExtractor;
	//バッファをアップロードする
	class BufferUploader;
	//ツールの貸し出しを行う
	class ToolLender;


	BufferContext
	(
		InstanceKey instanceKey_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
		CommandContextDiplomat* commandContextDiplomat_
	);

	~BufferContext();

	//Extractors
	std::unique_ptr<BufferInfoExtractor> bufferInfoExtractor;
	//ツール貸し出し
	std::unique_ptr<BufferContextDiplomat> diplomat;

	///ランタイムに入る前にNexusuがアップロード用の中間リソースを破棄する
	void DeleteBufferUploader(const InstanceKey& key_);
	
private:

	///複数のバッファのプールが定義されている
	BufferPoolSet bufferPoolSet;

	///バッファ生成クラス（本丸）
	std::unique_ptr<BufferCreator> bufferCreator;
	//生リソース生成
	std::unique_ptr<ResourceCreator> resourceCreator;
	//uploader
	std::unique_ptr<BufferUploader> bufferUploader;
	//ディスパッチャー
	std::unique_ptr<BufferDispatcher> bufferDispatcher;

};


struct BufferContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

struct BufferContext::BufferAccessKey
{
private:

	friend class BufferInfoExtractor;
	explicit BufferAccessKey() = default;
};


