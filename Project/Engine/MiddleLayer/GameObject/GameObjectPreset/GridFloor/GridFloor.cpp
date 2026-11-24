#include "PreCompileHeader.h"
#include "GridFloor.h"

#include "GameObjectSpecification.h"

void GridFloor::Update(SceneRuntimeInterface& sceneRuntimeInterface_)
{
	//static Vector3 r;
	//static Vector3 t;
	//static Vector4<float> c = {0.0f,0.0f ,0.0f ,1.0f};

	//r += {0.016f, 0.016f, 0.016f };
	//c += {0.0016f, 0.0025f, 0.005f, 0.0f };

	//for (int i = 0;i < 10;++i)
	//{
	//	p[i]->RefTransform(0).Rotate(r);
	//	p[i]->RefMaterials(0).Ref<Material::Type::kStandard>().baseColor = c;
	//}

	//t.data.z += 0.01666f;

	//RefSystem<Transform>().TranslatePosition(t);

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


	p = sceneInitInterface_.CreateModel<Model::MeshUpdateType::kStatic,Materials::UpdateType::kStatic>
		("Plane200x200Obj", renderStates, 1, "GridFloor");

	sceneInitInterface_.AttachMaterial<Material::Type::kGridLine>(p[0]->RefMaterials(0));
	
}

//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
//検索などはできる
void GridFloor::Start(SceneRuntimeInterface& sceneRuntimeInterface_)
{

}



