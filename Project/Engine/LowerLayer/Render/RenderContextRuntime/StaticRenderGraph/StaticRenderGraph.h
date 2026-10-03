#pragma once
#include "../../RenderContext.h"
#include "../../../Buffer/BufferDefinition/BufferTraits.h"

class DescriptorHeapContextDiplomat;
class CommandContextDiplomat;
class RuntimeWrapper;


class RenderContext::StaticRenderGraph
{
	//レンダーグラフの初期化手助けクラス
	class PSO_Builder;
	class PathBuilder;
	class RootSigBuilder;
	class PassSetUpper;
	class FinalRenderingSetupper;

	//Pathのランタイムを制御する
	class PathOperator;
	//共通描画コマンドをたたく
	class CommonCmdExecutor;
	//スワップチェーンのバックバッファに最終描画をする
	class FinalRenderer;

public:

	StaticRenderGraph
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		PSO_PoolDispatcher& psoDispatcher_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);

	~StaticRenderGraph();

	void Run
	(
		PSO_PoolDispatcher& psoDispatcher_,
		UINT const frameIndex_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
		CommandContextDiplomat& commandContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_
	);

private:

	struct BuildOutput
	{
		struct RootSigBuilder
		{
			//描画用巨大共通ルートシグネチャ
			ID3D12RootSignature* graphicsRootSig;
		};

		struct PathBuilder
		{
			//全てのPathのアドレス。本体は別コンテナクラスが所有。制御シーケンス通りにソートされている
			std::vector<PathBehavior*> sortedAllPathPtr;
		};

		struct PassSetUpper
		{
			///全てのパスが参照するバッファのIDが横一列に詰まっている
			///このIDを辿って、ランタイムの一歩目にsrvHeapIndexを詰めていく
			///極力static_castで高速にキャストしたいので分別しておく
			std::vector<BufferTraits::BufferTag> refBufferTagTrace;
			static constexpr UINT kNumRefBufferType = 2;
			std::array<std::vector<BufferUniqueID>, kNumRefBufferType > refBuffersArr;
			///パスが参照するバッファのsrvHeapIndexを詰めるためのバッファのID
			///UploadStructuredBufferなのでダブルです。中身の初期化もしていません
			BufferUniqueID targetFillInRefBufferID;
		};

		struct FinalRenderingSetupper
		{
			//スワップチェーンバッファの情報
			std::array<D3D12_CPU_DESCRIPTOR_HANDLE, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> rtvHandle;
			D3D12_VIEWPORT viewport;
			D3D12_RECT scissorRect;
			
		};

		RootSigBuilder rootSigBuilder;
		PathBuilder pathBuilder;
		PassSetUpper passSetUpper;

	};

	BuildOutput Build
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		PSO_PoolDispatcher& psoDispatcher_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);

	//Pathの更新処理を呼ぶ
	std::unique_ptr<PathOperator> pathOperator;
	//共通の描画コマンドをたたく
	std::unique_ptr<CommonCmdExecutor> commonCmdExecutor;	
};

