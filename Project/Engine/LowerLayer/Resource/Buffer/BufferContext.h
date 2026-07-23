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
	//生成したバッファの削除を担当
	class BufferDeferredReleaser;

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
	struct NexusFieldProof;
	//バッファのポインタを扱うものの証
	struct BufferAccessKey;
	//エージェント認証キー
	struct AgentKey;



	using DeleteBufferUploaderCommand = std::function<void()>;

	//BufferAssemblerとBufferCollectorをつかってバッファを作成する
	class BufferCreator;
	//BufferDescriptionをもとにバッファを組み立てる
	class BufferAssembler;
	//BufferUniqueIDから該当のバッファのアドレスを渡す
	class BufferDispatcher;
	//ランタイムパス構築に必要な情報の抽出とそのリソースのSwapを行う
	class BufferInfoExtractor;
	//バッファをアップロードする
	class BufferUploader;
	//ツールの貸し出しを行う
	class ToolLender;
	//生成したバッファを回収し分別する
	class BufferCollector;
	//生リソース生成
	class ResourceCreator;
	//代行者
	class ExecutionAgent;


	BufferContext
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_,
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
		CommandContextDiplomat* commandContextDiplomat_
	);

	~BufferContext();

	//ツール貸し出し
	std::unique_ptr<BufferContextDiplomat> diplomat;

	///ランタイムに入る前にNexusuがアップロード用の中間リソースを破棄する
	void DeleteBufferUploader(const NexusFieldProof& proof_, AgentKey agentKey_);
	
private:

	///複数のバッファのプールが定義されている
	std::unique_ptr<BufferPoolSet> bufferPoolSet;

	///バッファ生成クラス（本丸）
	std::unique_ptr<BufferCreator> bufferCreator;
	//生リソース生成
	std::unique_ptr<ResourceCreator> resourceCreator;
	//uploader
	std::unique_ptr<BufferUploader> bufferUploader;
	//ディスパッチャー
	std::unique_ptr<BufferDispatcher> bufferDispatcher;
	//コレクター
	std::unique_ptr<BufferCollector> bufferCollector;
	//Extractors
	std::unique_ptr<BufferInfoExtractor> bufferInfoExtractor;

};

struct BufferContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct BufferContext::BufferAccessKey
{
private:

	friend class BufferInfoExtractor;
	explicit BufferAccessKey() = default;
};

struct BufferContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};



