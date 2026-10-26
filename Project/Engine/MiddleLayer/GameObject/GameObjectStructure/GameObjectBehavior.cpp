#include "PreCompileHeader.h"
#include "GameObjectBehavior.h"


//外部
#include "../../../LowerLayer/Resource/Model/ModelStructure/Model.h"

GameObjectBehavior::GameObjectBehavior(Local_CreateLicence licence_)
{

}



void GameObjectBehavior::Init
(
	std::string const& name_,
	UINT id_,
	Model* model_
)
{
	name = name_;
	id = id_;

	//モデルがあるならそのメッシュの0番目とペアリングする
	if (model_)
	{
		model = model_;
		transform.BeParent(&model_->RefTransform(0));
	}
}

