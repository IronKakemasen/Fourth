#pragma once

class Nexus;
class BufferContextDiplomat;

class CameraContext
{

public:

	struct NexusFieldProof;
	//カメラのデータのバッチング処理を行う
	class CameraDataBatcher;
	//カメラのライブラリー
	class CameraLibrary;
	//カメラの登録を行う
	class CameraRegister;


	CameraContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~CameraContext();


private:

	std::unique_ptr<CameraLibrary> cameraLibrary;
	std::unique_ptr<CameraRegister> cameraRegister;
	

};


struct CameraContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

