#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassFwd.h"
#include "../PassDesc/PassDesc.h"


//外部
#include "../../../Resource/Buffer/BufferContext.h"


class RenderContext::RenderPassCreator
{
	class PassSettingsLoader;
	class PassBufferCreator;

public:

	RenderPassCreator
	(
		NexusFieldProof proof_,
		RenderPassContainer* container_, 
		BufferContextDiplomat& bufferContextDiplomat_
	);

	template<typename PassType>
	PassType* Create
	(
		NexusFieldProof proof_,
		std::string const passName_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{

		BufferContext::BufferCreator* bufferCreator = BorrowBufferCreator(bufferContextDiplomat_);

		PassDesc passDesc = CreateDesc(passName_, bufferCreator);

		return InstantiatePass(passDesc);
	}


private:

	//パスのディスクを生成
	PassDesc CreateDesc(std::string const passName_, BufferContext::BufferCreator* bufferCreator_);
	
	//パスの具現化
	template<typename PassType>
	PassType* InstantiatePass(NexusFieldProof proof_,PassDesc desc_);

	//bufferCreatorを借りる
	BufferContext::BufferCreator* BorrowBufferCreator(BufferContextDiplomat& bufferContextDiplomat_);

	//パスユニークの保管用
	RenderPassContainer* passContainer;
};

template<>
SceneTextureCreator* RenderContext::RenderPassCreator::InstantiatePass(NexusFieldProof proof_,PassDesc desc_);
