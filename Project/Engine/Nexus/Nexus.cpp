#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Device/DeviceContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/DescriptorHeap/DescriptorHeapContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Window/WindowContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/SwapChain/SwapChainContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Command/CommandContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/Shader/ShaderContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/Buffer/BufferContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/PSO/PSO_Context.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/RootSignature/RootSignatureContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/Mesh/MeshContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Render/RenderContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	std::string const fileName = "Nexus.cpp";
}

using namespace ProjectConfig::Window;

//Nexusクラスのインスタンスを制御するクラス
class Nexus::InstanceLimiter
{
public:
	static bool CanInstantiate();

	InstanceLimiter(const InstanceLimiter&) = delete;
	InstanceLimiter& operator=(const InstanceLimiter&) = delete;
	InstanceLimiter(InstanceLimiter&&) = delete;
	InstanceLimiter& operator=(InstanceLimiter&&) = delete;

private:
	int instanceCnt{};

	~InstanceLimiter() = default;
	InstanceLimiter() = default;
};

//Nexusクラスのインスタンスを1つに制限する
bool Nexus::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

Nexus::Nexus()
{
	Logger::Entry("Nexus: Constructor");

	//自身のインスタンス制限
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), "Nexusクラスが複数具現化されてます", fileName);

	InstantiateInSequence<InitSequence::kDeviceContext>();
	InstantiateInSequence<InitSequence::kWindowContext>();
	InstantiateInSequence<InitSequence::kDescriptorHeapContext>();
	InstantiateInSequence<InitSequence::kCommandContext>();
	InstantiateInSequence<InitSequence::kBufferContext>();
	InstantiateInSequence<InitSequence::kSwapChainContext>();
	InstantiateInSequence<InitSequence::kShaderContext>();
	InstantiateInSequence<InitSequence::kPSO_Context>();
	InstantiateInSequence<InitSequence::kRootSignatureContext>();
	InstantiateInSequence<InitSequence::kMeshContext>();
	InstantiateInSequence<InitSequence::kRenderContext>();
	InstantiateInSequence<InitSequence::kKickCommands>();
	InstantiateInSequence<InitSequence::kDeleteIntermediateResources>();

	ErrorMessageOutput::Assert::DetectError(next == InitSequence::kEnd, "初期化が正常に行われていない可能性がある", fileName);


	Logger::End("Nexus: Constructor");
}


Nexus::~Nexus()
{
	Finalize();
}











