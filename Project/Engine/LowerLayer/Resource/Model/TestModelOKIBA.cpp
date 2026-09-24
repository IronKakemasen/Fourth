#include "PreCompileHeader.h"
#include "TestModelOKIBA.h"

#include "CreateModelTools/ModelCreator.h"
#include "ModelStructure/ModelDescription/ModelDescription.h"


using namespace RenderStateComponent;
using namespace ShaderPathComponent;
using namespace RenderPassComponent;
using namespace StructuredBufferModelData;

TestModelOKIBA::TestModelOKIBA(ModelContext::ModelCreator* modelCreator_)
{
	Logger::Log("TESTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");

	RenderState cP;
	cP.blendModes.emplace_back(BlendMode::kOpaque);
	cP.blendModes.emplace_back(BlendMode::kAlphaBlend);
	cP.blendModes.emplace_back(BlendMode::kAdditive);

	cP.pass = Pass::kSceneOpaque;
	cP.cullMode = CullMode::kBack;
	cP.meshType = MeshType::kStatic;
	cP.materialTypes.emplace_back(MaterialType::kStandard);
	std::vector<RenderState> playerC;
	playerC.emplace_back(std::move(cP));

	std::vector<MaterialCPU> materials;

	player = modelCreator_->Create("PlayerObj", playerC, materials,"Player");


	RenderState cC;
	cC.blendModes.emplace_back(BlendMode::kOpaque);
	cC.pass = RenderPassComponent::Pass::kSceneOpaque;
	cC.cullMode = CullMode::kBack;
	cC.meshType = MeshType::kStatic;
	cC.materialTypes.emplace_back(MaterialType::kStandard);

	std::vector<RenderState> cubeC;
	cubeC.emplace_back(std::move(cC));

	cube = modelCreator_->Create("CubeGltf", cubeC, materials,"Cube");

}
