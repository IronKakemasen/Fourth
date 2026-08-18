#pragma once
#include "../../RenderContext.h"
#include "../PassDesc/PassDesc.h"
#include "../RenderPassContainer/RenderPassContainer.h"

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
		RenderPassContainer* container_
	);

	template<typename PassType>
	PassType* Create
	(
		NexusFieldProof proof_,
		std::string const passName_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{
		//すでに作成済みであればコンテナから渡す
		if (passContainer->Export<PassType>(proof_)) return passContainer->Export<PassType>(proof_);

		BufferContext::BufferCreator* bufferCreator = BorrowBufferCreator(bufferContextDiplomat_);

		PassDesc passDesc = CreateDesc(passName_, bufferCreator);

		return InstantiatePass<PassType>(proof_, passDesc);
	}


private:

	//パスのディスクを生成
	PassDesc CreateDesc(std::string const passName_, BufferContext::BufferCreator* bufferCreator_);
	
	//パスの具現化
	template<typename PassType>
	PassType* InstantiatePass(NexusFieldProof proof_, PassDesc desc_)
	{
		return passContainer->Import(proof_, std::move(std::make_unique<SceneTextureCreator>(proof_, std::move(desc_))));
	}

	//bufferCreatorを借りる
	BufferContext::BufferCreator* BorrowBufferCreator(BufferContextDiplomat& bufferContextDiplomat_);


	//パスユニークの保管用
	RenderPassContainer* passContainer;
};

