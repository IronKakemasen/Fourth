#pragma once

class DeviceContext;
class BufferContext;
class WindowContext;
class DescriptorHeapContext;
class SwapChainContext;
class CommandContext;
class ShaderContext;
class PSO_Context;


//交易場
class Nexus
{
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
	//シェーダのコンパイル、そのバイナリデータの管理
	std::unique_ptr<ShaderContext> shaderContext;
	//PSOの構築
	std::unique_ptr<PSO_Context> pso_context;

	void InstantiateCommandContext();
	void InstantiateSwapChainContext();
	void InstantiateDeviceContext();
	void InstantiateBufferContext();
	void InstantiateWindowContext();
	void InstantiateDescriptorHeapContext();
	void InstantiateShaderContext();
	void InstantiatePSO_Context();
	void Finalize();

};



