#pragma once
#include "../SceneBehavior.h"

//外部
#include "../../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

#include "../../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraSocket.h"


class CameraBehavior;

struct SceneBehavior::Output
{
	friend class SceneBehavior;

	auto const& WatchUsingCamera()const { return usingCamera; }
	auto const* WatchModelContainer()const { return modelContainer; }
	auto const& WatchLeftStaticModelBatchingCnt()const { return leftStaticModelBatchingCnt; }

private:

	//使用しているカメラ。更新必要
	std::unordered_map<CameraSocket, CameraBehavior*> usingCamera;
	//このシーンのモデルコンテナ
	ModelContext::FrontlineSystems::ModelContainer const* modelContainer = nullptr;
	//staticなモデルを毎回バッチング処理しないようにするため
	UINT leftStaticModelBatchingCnt = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;
};

