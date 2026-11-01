#include "PreCompileHeader.h"
#include "GridFloor.h"


void GridFloor::Update()
{

}

//ゲームオブジェクトのリセットに使用。シーンが切り替わった時に呼ばれる
void GridFloor::Reset()
{

}

//実質、コンストラクタの代わり
void GridFloor::Awake(SceneInitInterface* sceneInitInterface_)
{

}

//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
//検索などはできる
void GridFloor::Start(SceneRuntimeInterface* sceneRuntimeInterface_)
{
	
}


//using namespace RenderStateComponent;
//using namespace ShaderPathComponent;
//using namespace RenderPassComponent;
//using namespace StructuredBufferModelData;

	//RenderState cP;
	//cP.blendModes.emplace_back(BlendMode::kOpaque);
	//cP.blendModes.emplace_back(BlendMode::kAlphaBlend);
	//cP.blendModes.emplace_back(BlendMode::kAdditive);

	//cP.pass = Pass::kSceneOpaque;	
	//cP.cullMode = CullMode::kBack;
	//cP.meshType = MeshType::kStatic;
	//cP.materialTypes.emplace_back(MaterialType::kStandard);
	//std::vector<RenderState> playerC;
	//playerC.emplace_back(std::move(cP));

	//std::vector<MaterialCPU> materials;

	//p = CreateModel<Model::Type::kDynamic>("CubeGltf", playerC, materials, 10, "Player");
	//for (int i = 0;i < 10;++i)
	//{
	//	p[i]->RefTransform(0).TranslatePosition({ float(i) * 1.5f,0,4 });
	//}

	//RenderState cC;
	//cC.blendModes.emplace_back(BlendMode::kOpaque);
	//cC.pass = RenderPassComponent::Pass::kSceneOpaque;
	//cC.cullMode = CullMode::kBack;
	//cC.meshType = MeshType::kStatic;
	//cC.materialTypes.emplace_back(MaterialType::kStandard);

	//std::vector<RenderState> cubeC;
	//cubeC.emplace_back(std::move(cC));

	//auto c = CreateModel<Model::Type::kStatic>("CubeGltf", cubeC, materials, 5, "Cube");
