#include "PreCompileHeader.h"
#include "ModelContext.h"

#include "CreateModelTools/ModelDataCreator/ModelDataCreator.h"
#include "CreateModelTools/ModelSlotAllocator/ModelSlotAllocator.h"
#include "CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "CreateModelTools/ModelDescAssembler/ModelDescAssembler.h"
#include "CreateModelTools/ModelCreator.h"

#include "ModelContainer/ModelContainer.h"

#include "ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

#include "ModelContextDiplomat/ModelContextExecutionAgent/ModelContextExecutionAgent.h"
#include "ModelContextDiplomat/ModelContextToolLender/ModelContextToolLender.h"
#include "ModelContextDiplomat/ModelContextDiplomat.h"


#include "TestModelOKIBA.h"


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

	modelDataBatcher.reset(new ModelDataBatcher(proof_));
	Logger::Log("Instantiate: modelDataBatcher", fileName);


	modelDataCreator.reset
	(
		new ModelDataCreator
		(
			proof_, std::move(modelDataLoader),
			modelSlotAllocator.get(),
			modelDataBatcher.get(),
			bufferContextDiplomat_
		)
	);
	Logger::Log("Instantiate: ModelDataCreator", fileName);

	diplomat.reset
	(
		new ModelContextDiplomat
		(
			proof_,
			std::make_unique<ExecutionAgent>(proof_, modelDataLoader.get()),
			std::make_unique<ToolLender>(proof_, modelContainer.get())
		)
	);
	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);
	Logger::Log("Instantiate: ModelContextDiplomat", fileName);



	///てすとおおおおお
	testModelOKIBA.reset(new TestModelOKIBA(modelCreator.get()));

	Logger::End("ModelContext: Constructor");

}

ModelContext::~ModelContext()
{

}
