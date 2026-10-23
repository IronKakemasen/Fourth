#include "PreCompileHeader.h"
#include "RenderingTestScene.h"

using namespace RenderStateComponent;
using namespace ShaderPathComponent;
using namespace RenderPassComponent;
using namespace StructuredBufferModelData;


void RenderingTestScene::Init()
{
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

	auto p = CreateModel<Model::Type::kDynamic>("PlayerObj", playerC, materials, 1, "Player");


	RenderState cC;
	cC.blendModes.emplace_back(BlendMode::kOpaque);
	cC.pass = RenderPassComponent::Pass::kSceneOpaque;
	cC.cullMode = CullMode::kBack;
	cC.meshType = MeshType::kStatic;
	cC.materialTypes.emplace_back(MaterialType::kStandard);

	std::vector<RenderState> cubeC;
	cubeC.emplace_back(std::move(cC));

	auto c = CreateModel<Model::Type::kStatic>("CubeGltf", cubeC, materials, 5, "Cube");

}



