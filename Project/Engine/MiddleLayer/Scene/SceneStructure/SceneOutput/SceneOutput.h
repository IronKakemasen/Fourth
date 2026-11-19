#pragma once
#include "../SceneBehavior.h"

//外部
#include "../../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

#include "../../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraSocket.h"


class CameraBehavior;
struct MaterialBatchFormat;

struct SceneBehavior::Output
{
	friend class SceneBehavior;

	auto const& WatchUsingCamera()const { return usingCamera; }
	auto const* WatchModelContainer()const { return modelContainer; }
	auto const& WatchLeftStaticBatchingCnt()const { return leftStaticBatchingCnt; }
	auto const& WatchCollectedMaterialBatchFormatsArr()const{return (*materialBatchFormatsPtr);}

private:
	//全描画対象のバッチングに必要なMaterialBatchFormatのコンテナ
	std::array<std::vector<MaterialBatchFormat>, (UINT)Materials::UpdateType::kCount>*
		materialBatchFormatsPtr = nullptr;
	//使用しているカメラ。更新必要
	std::unordered_map<CameraSocket, CameraBehavior*> usingCamera;
	//このシーンのモデルコンテナ
	ModelContext::FrontlineSystems::ModelContainer const* modelContainer = nullptr;
	//static対象を毎回バッチング処理しないようにするため
	UINT leftStaticBatchingCnt = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;
};

