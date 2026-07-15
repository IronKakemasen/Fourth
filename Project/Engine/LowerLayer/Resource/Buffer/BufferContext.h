#pragma once

class Nexus;
class DescriptorHeapContext;
class GPUBufferBehavior;


class BufferContext
{
	//生成したバッファを回収し分別する
	class BufferCollector;
	//生成したバッファの削除を担当
	class BufferDeferredReleaser;
	//生リソース生成
	class ResourceCreator;
	//BufferAssemblerとBufferCollectorをつかってバッファを作成する
	class BufferCreator;
	//BufferUniqueIDから該当のバッファのアドレスをキャストして渡す
	class BufferDispatcher;

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
		//ColorBufferやDepthStencilBufferなどレンダーターゲットなバッファプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> renderTargetBufferPool;
		//computeBufferのような、コンピュートシェーダをかませるバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> computeBufferPool;
		//ConstantBufferやUploadStructuredBufferのようなフレームバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> frameBufferPool;
		//staticStructuredBufferやtextureBufferのような、読みしかしない確定のシングルバッファのプール
		std::vector<std::unique_ptr<GPUBufferBehavior>> readOnlyBufferPool;

		//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
		std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>> bufferLocationMap;

		//RegisterTypeがキーのテーブル
		std::vector<std::unique_ptr<GPUBufferBehavior>>* ContainerTable(BufferContext::RegisterType type_);
	};

public:

	//自身のインスタンス化キー
	struct InstanceKey;
	//バッファのポインタを扱うものの証
	struct BufferAccessKey;

	//ResourceCreatorとViewCreatorでバッファを生成
	class BufferAssembler;
	//ランタイムパス構築に必要な情報の抽出とそのリソースのSwapを行う
	class BufferInfoExtractor;

	BufferContext
	(
		InstanceKey instanceKey_,
		CreateResourceCommand createResourceCommand_,
		DescriptorHeapContext* descriptorHeapContext_
	);

	~BufferContext();

	///バッファ生成クラス（本丸）
	std::unique_ptr<BufferCreator> bufferCreator;
	//ディスパッチャー
	std::unique_ptr<BufferDispatcher> bufferDispatcher;
	//Extractors
	std::unique_ptr<BufferInfoExtractor> BufferInfoExtractor;

private:

	//複数のバッファのプールが定義されている
	BufferPoolSet bufferPoolSet;


	void InstantiateBufferCreator
	(
		InstanceKey instanceKey_,
		CreateResourceCommand createResourceCommand_,
		DescriptorHeapContext* descriptorHeapContext_
	);

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

