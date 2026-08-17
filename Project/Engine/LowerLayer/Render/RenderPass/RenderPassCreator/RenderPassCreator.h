#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassFwd.h"
#include "../PassDesc/PassDesc.h"


//外部
#include "../../../Resource/Buffer/BufferContext.h"
#include "../../../Resource/Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../Resource/Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../Resource/Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"


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
		Local_CreateRenderPassLicence licence_,
		std::string const passName_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{
		BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> borrowLicence;
		BufferContext::BufferCreator* bufferCreator =
			bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferCreator>(borrowLicence);

		PassDesc passDesc = CreateDesc(passName_, bufferCreator);

		return InstantiatePass(passDesc);
	}


private:

	PassDesc CreateDesc(std::string const passName_, BufferContext::BufferCreator* bufferCreator_);
	
	template<typename PassType>
	PassType* InstantiatePass(Local_CreateRenderPassLicence licence_,PassDesc desc_);

	RenderPassContainer* passContainer;
};

template<>
SceneTextureCreator* RenderContext::RenderPassCreator::InstantiatePass(Local_CreateRenderPassLicence licence_,PassDesc desc_);
