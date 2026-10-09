#pragma once

class Nexus;
class BufferContextDiplomat;

class CameraContext
{

public:

	struct NexusFieldProof;
	//カメラのデータのバッチング処理を行う
	class CameraDataBatcher;


	CameraContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~CameraContext();


private:


};


struct CameraContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

