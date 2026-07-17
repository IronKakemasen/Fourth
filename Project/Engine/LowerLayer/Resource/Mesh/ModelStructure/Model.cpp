#include "PreCompileHeader.h"
#include "Model.h"

#include "ModelDescription.h"

Model::Model(std::unique_ptr<ModelDescription>&& desc_)
	:desc(std::move(desc_))
{

}
