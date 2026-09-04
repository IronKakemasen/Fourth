#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapPool/DescriptorHeapPool.h"
#include "ViewCreator/ViewCreator.h"
#include "DescriptorHeapPoolContainer/DescriptorHeapPoolContainer.h"

#include "DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"
#include "DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"

//外部
#include "../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

using namespace ProjectConfig::Core;

DescriptorHeapContext::DescriptorHeapContext
(
	NexusFieldProof proof_,
	DeviceContextDiplomat& deviceContextDiplomat_
)
{
	Logger::Entry("DescriptorHeapContext: Constructor");

	
	//各種DescriptorHeapを生成する
	descriptorHeapPoolContainer.reset(new DescriptorHeapPoolContainer(proof_));
	DescriptorHeapCreator descriptorHeapCreator(proof_, *descriptorHeapPoolContainer.get(), deviceContextDiplomat_);

	viewCreator.reset
	(
		new ViewCreator
		(
			proof_,
			*descriptorHeapPoolContainer.get(),
			deviceContextDiplomat_
		)
	);
	Logger::Log("Instantiate: ViewCreator", fileName);


	diplomat.reset
	(
		new DescriptorHeapContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, viewCreator.get())
		)
	);
	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: DescriptorHeapContextDiplomat", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
