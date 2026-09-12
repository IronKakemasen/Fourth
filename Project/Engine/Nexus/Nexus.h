#pragma once

class DeviceContext;
class BufferContext;
class WindowContext;
class DescriptorHeapContext;
class SwapChainContext;
class CommandContext;
class ShaderContext;
class PSO_Context;
class RootSignatureContext;
class RenderContext;
class ModelContext;
class TextureContext;


//交易場
class Nexus
{
	//初期化・生成順序
	enum class InitSequence
	{
		kLoadAllJsonFiles,

		kDeviceContext,
		kWindowContext,
		kDescriptorHeapContext,
		kCommandContext,
		kBufferContext,
		kSwapChainContext,
		kShaderContext,
		kPSO_Context,
		kRootSignatureContext,
		kTextureContext,
		kModelContext,
		kRenderContext,


		kUploadAllResources,
		kKickCommands,
		kDeleteIntermediateResources,
		kSortOutGlobalConstantBuffers


		,kEnd
	}nextInit = InitSequence(0);

	//終了処理順序
	enum class FinalizeSequence
	{
		kCommandContext,
		kWindowContext,
		kCoUninitialize



		,kEnd
	}nextFin = FinalizeSequence(0);

public:

	~Nexus();
	Nexus();

	Nexus(const Nexus&) = delete;
	Nexus& operator=(const Nexus&) = delete;
	Nexus(Nexus&&) = delete;
	Nexus& operator=(Nexus&&) = delete;

	void Run();

private:

	//Nexusのインスタンスを1つに制限するためのシングルトンクラス
	class InstanceLimiter;


	//IDXGIFactory7、IDXGIAdapter4、ID3D12Device8を持ち、コアパーツによるコマンドを提供したりする
	std::unique_ptr<DeviceContext> deviceContext;
	//ウィンドウを制御するもの
	std::unique_ptr<WindowContext> windowContext;
	//DescriptorHeapを作り、各種バッファのviewを生成するツールを持つ
	std::unique_ptr<DescriptorHeapContext> descriptorHeapContext;
	//GPUバッファを生成・管理
	std::unique_ptr<BufferContext> bufferContext;
	//コマンド関連のコアパーツの管理
	std::unique_ptr<CommandContext> commandContext;
	//SwapChain周りを制御するもの
	std::unique_ptr<SwapChainContext> swapChainContext;
	//シェーダのコンパイル、データの保持
	std::unique_ptr<ShaderContext> shaderContext;
	//PSOの生成とデータの保持
	std::unique_ptr<PSO_Context> pso_context;
	//ルートシグネチャの生成とデータの保持
	std::unique_ptr<RootSignatureContext> rootSignatureContext;
	//PSOの管理、描画パスの構築
	std::unique_ptr<RenderContext> renderContext;
	//モデルクラスの生成、管理
	std::unique_ptr<ModelContext> modelContext;
	//テクスチャファイルの読み込み、データ保持
	std::unique_ptr<TextureContext> textureContext;


	
	//各Contextクラスの具現化、初期化を行う
	template<InitSequence initSequence>
	void Init();

	///簡易だけども初期化順序制御を行いながら初期化する
	template<InitSequence next_>
	void InitializeInSequence()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			nextInit == next_ ,
			"初期化が正常に行われていない可能性がある",
			"Nexus.h"
		);

		Init<next_>();

		nextInit = InitSequence((UINT)nextInit + 1);
	}

	//終了処理を行う
	template<FinalizeSequence finalizeSequence>
	void Finalize();

	///終了処理バージョン
	template<FinalizeSequence next_>
	void FinalizeInSequence()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			nextFin == next_,
			"終了処理が正常に行われていない可能性がある",
			"Nexus.h"
		);

		Finalize<next_>();

		nextFin = FinalizeSequence((UINT)nextFin + 1);
	}

};




