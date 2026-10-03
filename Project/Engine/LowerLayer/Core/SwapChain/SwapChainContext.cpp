#include "SwapChainContext.h"
#include "SwapChainBuffer/SwapChainBuffer.h"
#include "Presenter/Presenter.h"
#include "SwapChainContextBuilder/SwapChainContextBuilder.h"


using namespace ProjectConfig::Render;
using namespace ProjectConfig::Window;

namespace
{
	std::string fileName = "SwapChainContext.cpp";
}

SwapChainContext::SwapChainContext
(
	NexusFieldProof proof_,
	DescriptorHeapContextDiplomat& descriptorheapContextDiplomat_,
	CommandContextDiplomat& commandContextDiplomat_,
	DeviceContextDiplomat& deviceContextDiplomat_,
	WindowContextDiplomat& windowContextDiplomat_
)
{
	Logger::Entry("SwapChainContext: Constructor");

	std::tie(swapChainBuffer, swapChain) = Builder::Build
	(
		proof_,
		descriptorheapContextDiplomat_,
		commandContextDiplomat_,
		deviceContextDiplomat_,
		windowContextDiplomat_
	);


	presenter.reset(new Presenter(swapChain.Get()));
	Logger::Log("Instantiate: Presenter", fileName);


	Logger::End("SwapChainContext: Constructor");
}

SwapChainContext::~SwapChainContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
