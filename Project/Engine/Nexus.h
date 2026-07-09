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


//交易場
class Nexus
{
	//初期化・生成順序
	enum class InitSequence
	{
		kDeviceContext,
		kWindowContext,
		kDescriptorHeapContext,
		kBufferContext,
		kCommandContext,
		kSwapChainContext,
		kShaderContext,
		kPSO_Context,
		kRootSignatureContext,
		kRenderContext


		,kEnd
	}next = InitSequence::kDeviceContext;

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


	//IDXGIFactory7、IDXGIAdapter4、ID3D12Device8を持っている。
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
	

	//各Contextクラスの具現化、初期化を行う
	template<InitSequence initSequence>
	void Instantiate();


	///簡易だけども初期化順序制御を行いながら初期化する
	template<InitSequence next_>
	void InstantiateInSequence()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			next == next_ , 
			"初期化が正常に行われていない可能性がある",
			"Nexus.h"
		);

		Instantiate<next_>();

		next = InitSequence((UINT)next + 1);
	}

	void Finalize();

};




