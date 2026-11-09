#include "PreCompileHeader.h"
#include "GridFloor.h"

#include "GameObjectSpecification.h"

void GridFloor::Update(SceneRuntimeInterface& sceneRuntimeInterface_)
{

}

//ゲームオブジェクトのリセットに使用。シーンが切り替わった時に呼ばれる
void GridFloor::Reset()
{

}

//実質、コンストラクタの代わり
void GridFloor::Awake(SceneInitInterface& sceneInitInterface_)
{
	RenderState cP;
	cP.blendModes.emplace_back(BlendMode::kOpaque);
	cP.blendModes.emplace_back(BlendMode::kAlphaBlend);
	cP.blendModes.emplace_back(BlendMode::kAdditive);

	cP.pass = Pass::kSceneOpaque;	
	cP.cullMode = CullMode::kBack;
	cP.meshType = MeshType::kStatic;
	cP.materialTypes.emplace_back(Material::Type::kStandard);
	std::vector<RenderState> playerC;
	playerC.emplace_back(std::move(cP));

	std::vector<MaterialCPU> materials;
	materials.resize(1);
	materials[0].samplerState = SamplerState::kLinearClamp;

	p = sceneInitInterface_.CreateModel<Model::Type::kDynamic>("Plane200x200Obj", playerC, materials, 1, "Player");
	for (int i = 0;i < 1;++i)
	{
		p[i]->RefTransform(0).TranslatePosition({ 1.5f,-5,100 });
	}

	
}

//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
//検索などはできる
void GridFloor::Start(SceneRuntimeInterface& sceneRuntimeInterface_)
{
	
}



