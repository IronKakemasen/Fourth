#include "PreCompileHeader.h"
#include "Model.h"


Model::Model(const ModelDescription& modelDesc_)
	:modelDesc(modelDesc_)
{
	changeableStatus.blendMode = modelDesc_.WatchRenderStates()[0].blendModes[0];
	changeableStatus.materialType = modelDesc_.WatchRenderStates()[0].materialTypes[0];

}

std::string const Model::WatchName()const
{
	return modelDesc.WatchRenderStates()[0].modelName;
}