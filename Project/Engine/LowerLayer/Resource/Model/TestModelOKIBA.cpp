#include "PreCompileHeader.h"
#include "TestModelOKIBA.h"

#include "CreateModelTools/ModelCreator.h"
#include "ModelStructure/ModelDescription.h"


using namespace RenderStateComponent;
using namespace ShaderPathComponent;


TestModelOKIBA::TestModelOKIBA(ModelContext::ModelCreator* modelCreator_)
{
	Logger::Log("TESTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");

	ModelDescription::Configurable cP;
	cP.blendModes.emplace_back(BlendMode::kOpaque);
	cP.passes |= RenderPass::kSceneTexture;

	cP.cullMode = CullMode::kBack;
	cP.meshType = ShaderPathComponent::MeshType::kStatic;
	cP.materialType = ShaderPathComponent::MaterialType::kStandard;

	std::vector<ModelDescription::Configurable> playerC;
	playerC.emplace_back(std::move(cP));

	player = modelCreator_->Create("PlayerObj", playerC,"Player");


	ModelDescription::Configurable cC;
	cC.blendModes.emplace_back(BlendMode::kOpaque);
	cC.passes|= RenderPass::kSceneTexture;
	cC.cullMode = CullMode::kBack;
	cC.meshType = ShaderPathComponent::MeshType::kStatic;
	cC.materialType = ShaderPathComponent::MaterialType::kStandard;

	std::vector<ModelDescription::Configurable> cubeC;
	cubeC.emplace_back(std::move(cC));

	cube = modelCreator_->Create("CubeGltf", cubeC,"Cube");

}
