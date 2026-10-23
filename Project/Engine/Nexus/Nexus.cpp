#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/DebugSystem/DebugContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Device/DeviceContext.h"
#include "../LowerLayer/Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../LowerLayer/Core/Window/WindowContext.h"
#include "../LowerLayer/Core/SwapChain/SwapChainContext.h"
#include "../LowerLayer/Core/Command/CommandContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Resource/Shader/ShaderContext.h"
#include "../LowerLayer/Resource/PSO/PSO_Context.h"
#include "../LowerLayer/Resource/RootSignature/RootSignatureContext.h"
#include "../LowerLayer/Resource/Model/ModelContext.h"
#include "../LowerLayer/Resource/Texture/TextureContext.h"
#include "../LowerLayer/Resource/Camera/CameraContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Buffer/BufferContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../MiddleLayer/Render/RenderContext.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../MiddleLayer/Scene/SceneContext.h"

namespace
{
	std::string const fileName = "Nexus.cpp";
}




Nexus::Nexus(aFourthProof proof_)
{
	Logger::Entry("Nexus: Constructor");

	PrimaryInit();
	
	Logger::End("Nexus: Constructor");
}


Nexus::~Nexus()
{
	Logger::Entry("Nexus: Destructor");


	FinalizeInSequence<FinalizeSequence::kCommandContext>();
	FinalizeInSequence<FinalizeSequence::kWindowContext>();

	ErrorMessageOutput::Assert::DetectError(nextFin == FinalizeSequence::kEnd, "終了処理が正常に行われていない可能性がある", fileName);

	Logger::End("Nexus: Destructor");

}

void Nexus::PrimaryInit()
{
	InitializeInSequence<InitSequence::kDebugContext>();
	InitializeInSequence<InitSequence::kDeviceContext>();
	InitializeInSequence<InitSequence::kWindowContext>();
	InitializeInSequence<InitSequence::kDescriptorHeapContext>();
	InitializeInSequence<InitSequence::kCommandContext>();
	InitializeInSequence<InitSequence::kBufferContext>();
	InitializeInSequence<InitSequence::kSwapChainContext>();
	InitializeInSequence<InitSequence::kShaderContext>();
	InitializeInSequence<InitSequence::kPSO_Context>();
	InitializeInSequence<InitSequence::kRootSignatureContext>();
	InitializeInSequence<InitSequence::kTextureContext>();
	InitializeInSequence<InitSequence::kModelContext>();
	InitializeInSequence<InitSequence::kCameraContext>();
	InitializeInSequence<InitSequence::kSceneContext>();

}

//2段階目初期化
void Nexus::SecondaryInit(aFourthProof proof_)
{
	InitializeInSequence<InitSequence::kRenderContext>();
	InitializeInSequence<InitSequence::kUploadAllResources>();
	InitializeInSequence<InitSequence::kKickCommands>();
	InitializeInSequence<InitSequence::kDeleteBufferUploaderCache>();
	InitializeInSequence<InitSequence::kSortOutGlobalConstantBuffers>();
	InitializeInSequence<InitSequence::kDeleteModelDataCache>();

	ErrorMessageOutput::Assert::DetectError(nextInit == InitSequence::kEnd, "初期化が正常に行われていない可能性がある", fileName);
}


