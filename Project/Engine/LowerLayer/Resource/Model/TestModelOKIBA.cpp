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

	ModelDescription::RenderState cP;
	cP.blendModes.emplace_back(BlendMode::kOpaque);
	cP.blendModes.emplace_back(BlendMode::kAlphaBlend);
	cP.blendModes.emplace_back(BlendMode::kAdditive);

	cP.pass = Pass::kSceneTextureCreatorOpaque;
	cP.cullMode = CullMode::kBack;
	cP.meshType = MeshType::kStatic;
	cP.materialType = MaterialType::kStandard;
	std::vector<ModelDescription::RenderState> playerC;
	playerC.emplace_back(std::move(cP));

	std::vector<MaterialCPU> materials;

	player = modelCreator_->Create("PlayerObj", playerC, materials,"Player");


	ModelDescription::RenderState cC;
	cC.blendModes.emplace_back(BlendMode::kOpaque);
	cC.pass = RenderPassComponent::Pass::kSceneTextureCreatorOpaque;
	cC.cullMode = CullMode::kBack;
	cC.meshType = MeshType::kStatic;
	cC.materialType = MaterialType::kStandard;

	std::vector<ModelDescription::RenderState> cubeC;
	cubeC.emplace_back(std::move(cC));

	cube = modelCreator_->Create("CubeGltf", cubeC, materials,"Cube");

}
