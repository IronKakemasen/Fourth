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
	RenderState renderState;
	renderState.blendModes.emplace_back(BlendMode::kOpaque);
	renderState.pass = Pass::kSceneOpaque;	
	renderState.cullMode = CullMode::kBack;
	renderState.meshType = MeshType::kStatic;
	renderState.materialTypes.emplace_back(Material::Type::kGridLine);

	std::vector<RenderState> renderStates;
	renderStates.emplace_back(std::move(renderState));

	plane = sceneInitInterface_.CreateModel<Model::MeshUpdateType::kStatic,Materials::UpdateType::kStatic>
		("Plane200x200Obj", renderStates, 1, "GridFloor")[0];

	sceneInitInterface_.AttachMaterial<Material::Type::kGridLine>(plane->RefMaterials(0));
	
}

//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
//検索などはできる
void GridFloor::Start(SceneRuntimeInterface& sceneRuntimeInterface_)
{

}



