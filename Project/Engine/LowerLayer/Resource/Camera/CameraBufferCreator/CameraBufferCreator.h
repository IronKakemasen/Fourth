#pragma once
#include "../CameraContext.h"


class CameraContext::CameraBufferCreator
{
	friend class CameraContext;

	//カメラデータ配列のバッファを作成し、そのsrvHeapIndexの定数バッファを作成。
	//カメラデータ配列のバッファのIDはCameraDataBatcherがランタイムでバッチングするために所持する
	static void Create
	(
		NexusFieldProof proof_,
		CameraDataBatcher& cameraDataBatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


};

