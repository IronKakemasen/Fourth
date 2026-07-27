#include "PreCompileHeader.h"
#include "ModelContext.h"

#include "CreateModelTools/ModelDataCreator/ModelDataCreator.h"
#include "CreateModelTools/ModelSlotAllocator/ModelSlotAllocator.h"
#include "CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "CreateModelTools/ModelDescAssembler/ModelDescAssembler.h"
#include "CreateModelTools/ModelCreator.h"
#include "ModelContainer/ModelContainer.h"

#include "MeshContextDiplomat/MeshContextExecutionAgent/MeshContextExecutionAgent.h"
#include "MeshContextDiplomat/MeshContextDiplomat.h"

namespace
{
	auto const fileName = "ModelContext.cpp";
}


ModelContext::ModelContext(NexusFieldProof proof_,BufferContextDiplomat* bufferContextDiplomat_)
{
	Logger::Entry("ModelContext: Constructor");

	modelSlotAllocator.reset(new ModelSlotAllocator(proof_));
	Logger::Log("Instantiate: modelSlotAllocator", fileName);

	std::unique_ptr<ModelDataLoader> modelDataLoader(std::make_unique<ModelDataLoader>(proof_));
	Logger::Log("Instantiate: ModelDataLoader", fileName);

	modelContainer.reset(new ModelContainer(proof_));
	Logger::Log("Instantiate: modelContainer", fileName);

	modelCreator.reset
	(
		new ModelCreator
		(
			proof_,
			std::make_unique<ModelDescAssembler>(proof_, modelSlotAllocator.get()),
			modelContainer.get()
		)
	);

	Logger::Log("Instantiate: ModelDescAssembler", fileName);
	Logger::Log("Instantiate: ModelCreator", fileName);

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


	Logger::End("ModelContext: Constructor");

}

ModelContext::~ModelContext()
{

}
