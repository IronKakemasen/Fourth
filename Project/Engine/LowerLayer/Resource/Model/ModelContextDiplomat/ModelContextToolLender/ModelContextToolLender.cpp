#include "PreCompileHeader.h"
#include "ModelContextToolLender.h"
#include "../../ModelContainer/ModelContainer.h"

ModelContext::ToolLender::ToolLender
(
	NexusFieldProof proof_, 
	ModelContext::ModelContainer* modelContainer_
)
{
	std::get<ModelContext::ModelContainer*>(tools) = modelContainer_;

}
