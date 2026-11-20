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
	sceneInitInterface_.AttachSystem<Transform>(*this);

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

	std::vector<Material::StandardCPU> materials;
	materials.resize(1);
	materials[0].albedoTexSamplerState = SamplerState::kLinearClamp;

	p = sceneInitInterface_.CreateModel<Model::MeshUpdateType::kDynamic,Materials::UpdateType::kDynamic>
		("Plane200x200Obj", playerC, materials, 10, "Player");
	//for (int i = 0;i < 10;++i)
	//{
	//	RefSystem<Transform>().BeParent(&p[i]->RefTransform(0));

	//	p[i]->RefTransform(0).TranslatePosition({ -8.0f + float(2.5f * float(i)),-2.0,1.0f });
	//}

	
}

//更新処理の直前に呼ばれる。他のゲームオブジェクトはこの時点で生成されているので
//検索などはできる
void GridFloor::Start(SceneRuntimeInterface& sceneRuntimeInterface_)
{

}



