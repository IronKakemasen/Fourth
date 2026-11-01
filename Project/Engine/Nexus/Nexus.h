#pragma once

template<typename... SceneTypes>
class aFourth;

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
class CameraContext;
class DebugContext;
class SceneContext;
class GameObjectContext;


//交易場
class Nexus
{
public:

	//エンジンクラスしかインスタンス化はさせません
	struct aFourthProof;

	Nexus(aFourthProof proof_);
	~Nexus();

	Nexus(const Nexus&) = delete;
	Nexus& operator=(const Nexus&) = delete;
	Nexus(Nexus&&) = delete;
	Nexus& operator=(Nexus&&) = delete;

	//更新処理
	void Run(aFourthProof proof_);

	//2段階目初期化
	void SecondaryInit(aFourthProof proof_);

	//エンジンインターフェースがシーンのインスタンス化メソッドを定義するために必要
	template<typename ContextType>
	auto& AccessContext(aFourthProof const& proof_)
	{
		if		constexpr (std::is_same_v<ContextType, ModelContext>)		return *modelContext;
		else if constexpr (std::is_same_v<ContextType, CameraContext>)		return *cameraContext;
		else if constexpr (std::is_same_v<ContextType, SceneContext>)		return *sceneContext;
		else if constexpr (std::is_same_v<ContextType, GameObjectContext>)	return *gameObjectContext;

	}

private:

	//初期化・生成順序
	enum class InitSequence
	{
		kDebugContext,
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
		kGameObjectContext,
		kCameraContext,
		kSceneContext,
		//ここまではコンストラクタ


		//コンストラクタからここまでに、シーン(モデル)の作成が完了してなければならない
		kRenderContext,

		kUploadAllResources,
		kKickCommands,
		kDeleteBufferUploaderCache,
		kSortOutGlobalConstantBuffers,
		kDeleteModelDataCache,					///モデルデータキャッシュの削除は、アプリ層の初期化が終わったあと

		kEnd
	}nextInit = InitSequence::kDebugContext;

	//終了処理順序
	enum class FinalizeSequence
	{
		kCommandContext,
		kWindowContext


		, kEnd
	}nextFin = FinalizeSequence::kCommandContext;

	//デバッガー。DebugLayer, PointerValidator, LeakChecker
	std::unique_ptr<DebugContext> debugContext;
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
	//ゲームオブジェクトの生成、管理
	std::unique_ptr<GameObjectContext> gameObjectContext;
	//モデルクラスの生成、管理
	std::unique_ptr<ModelContext> modelContext;
	//テクスチャファイルの読み込み、データ保持
	std::unique_ptr<TextureContext> textureContext;
	//カメラの定義、作成、バッチング処理
	std::unique_ptr<CameraContext> cameraContext;
	//シーンの作成、保持、コントロール、シーンデータのバッチングを行う
	std::unique_ptr<SceneContext> sceneContext;


	//一段階目初期化
	void PrimaryInit();

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

struct Nexus::aFourthProof
{
private:

	template<typename... SceneTypes>
	friend class aFourth;

	explicit aFourthProof() = default;
};



