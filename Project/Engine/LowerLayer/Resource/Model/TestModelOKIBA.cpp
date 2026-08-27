#include "PreCompileHeader.h"
#include "TestModelOKIBA.h"

#include "CreateModelTools/ModelCreator.h"
#include "ModelStructure/ModelDescription/ModelDescription.h"


using namespace RenderStateComponent;
using namespace ShaderPathComponent;


TestModelOKIBA::TestModelOKIBA(ModelContext::ModelCreator* modelCreator_)
{
	Logger::Log("TESTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");

	ModelDescription::RenderState cP;
	cP.blendModes.emplace_back(BlendMode::kOpaque);
	cP.passes |= RenderPass::kSceneTextureOpaque;

	cP.cullMode = CullMode::kBack;
	cP.meshType = ShaderPathComponent::MeshType::kStatic;
	cP.materialType = ShaderPathComponent::MaterialType::kStandard;

	std::vector<ModelDescription::RenderState> playerC;
	playerC.emplace_back(std::move(cP));

	player = modelCreator_->Create("PlayerObj", playerC,"Player");


	ModelDescription::RenderState cC;
	cC.blendModes.emplace_back(BlendMode::kOpaque);
	cC.passes|= RenderPass::kSceneTextureOpaque;
	cC.cullMode = CullMode::kBack;
	cC.meshType = ShaderPathComponent::MeshType::kStatic;
	cC.materialType = ShaderPathComponent::MaterialType::kStandard;

	std::vector<ModelDescription::RenderState> cubeC;
	cubeC.emplace_back(std::move(cC));

	cube = modelCreator_->Create("CubeGltf", cubeC,"Cube");

}
