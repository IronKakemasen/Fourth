#include "PreCompileHeader.h"
#include "MeshContext.h"
#include "CreateModelTools/ModelDataCreator/ModelDataCreator.h"
#include "CreateModelTools/ModelSlotAllocator/ModelSlotAllocator.h"
#include "CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "MeshContextRuntime/ModelAssembler/ModelAssembler.h"
#include "MeshContextDiplomat/MeshContextExecutionAgent/MeshContextExecutionAgent.h"
#include "MeshContextDiplomat/MeshContextDiplomat.h"

namespace
{
	auto const fileName = "MeshContext.cpp";
}


MeshContext::MeshContext(NexusFieldProof proof_,BufferContextDiplomat* bufferContextDiplomat_)
{
	Logger::Entry("MeshContext: Constructor");

	modelSlotAllocator.reset(new ModelSlotAllocator(proof_));
	Logger::Log("Instantiate: modelSlotAllocator", fileName);

	std::unique_ptr<ModelDataLoader> modelDataLoader(std::make_unique<ModelDataLoader>(proof_));
	Logger::Log("Instantiate: ModelDataLoader", fileName);

	modelAssembler.reset(new ModelAssembler(proof_, modelSlotAllocator.get()));
	Logger::Log("Instantiate: ModelAssembler", fileName);

	diplomat.reset
	(
		new MeshContextDiplomat
		(
			proof_,
			std::make_unique<ExecutionAgent>(proof_, modelDataLoader.get())
		)
	);
	Logger::Log("Instantiate: ExecutionAgent", fileName);
	Logger::Log("Instantiate: MeshContextDiplomat", fileName);

	modelDataCreator.reset
	(
		new ModelDataCreator
		(
			proof_,std::move(modelDataLoader), 
			modelSlotAllocator.get(),
			bufferContextDiplomat_
		)
	);
	Logger::Log("Instantiate: ModelDataCreator", fileName);


	Logger::End("MeshContext: Constructor");

}

MeshContext::~MeshContext()
{

}
