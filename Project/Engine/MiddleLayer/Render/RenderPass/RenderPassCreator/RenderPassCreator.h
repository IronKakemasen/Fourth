#pragma once
#include "../../RenderContext.h"
#include "../PassDesc/PassDesc.h"
#include "../RenderPassContainer/RenderPassContainer.h"
#include "../AllRenderPass/RenderPassTraits.h"



class RenderContext::RenderPassCreator
{
	class PassSettingsLoader;
	class PassBufferCreator;

public:

	RenderPassCreator
	(
		NexusFieldProof proof_,
		RenderPassContainer& container_
	);

	template<typename PassType>
	PassType* Create
	(
		NexusFieldProof proof_,
		std::string const& passName_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{
		//すでに作成済みであればコンテナから渡す
		auto* pass = passContainer.Export<PassType>(proof_);
		if (pass) return pass;

		//パスのディスクを作成
		std::unique_ptr<PassDesc> passDesc = CreateDesc(passName_, bufferContextDiplomat_);

		return InstantiatePass<PassType>(proof_, std::move(passDesc));
	}


	std::unordered_map<std::string, BufferUniqueID> const& WatchPassBufferCache(NexusFieldProof proof_)const;
	
	std::unordered_map<std::string, std::vector<RequiredBufferInfo::ColorBuffer*>> const&
		WatchColorBufferInfosMapCache(NexusFieldProof proof_)const;
	
	std::unordered_map<std::string, RequiredBufferInfo::DepthStencilBuffer*> const& 
		WatchDepthBufferInfoMapCache(NexusFieldProof proof_)const;


private:

	//パスのディスクを生成
	std::unique_ptr<PassDesc> CreateDesc(std::string const& passName_, BufferContextDiplomat& bufferContextDiplomat_);
	
	//パスの具現化
	template<typename PassType>
	PassType* InstantiatePass(NexusFieldProof proof_, std::unique_ptr<PassDesc> desc_)
	{
		return passContainer.Import
		(
			proof_, 
			std::move(std::make_unique<PassType>(proof_, std::move(desc_)))
		);
	}

	//パスユニークの保管用
	RenderPassContainer& passContainer;
	
	//後に検索のため一時的にパスのバッファを保存しておくもの。ま、このクラス自体が消滅するんだけどね
	//参照バッファ検索時に使用
	std::unordered_map<std::string, BufferUniqueID> passBufferCache;
	//そのRequiredBufferInfo::ColorBuffer,DepthStencilBufferバージョン
	//書き込みシェアバッファ検索時に使用
	std::unordered_map<std::string, std::vector<RequiredBufferInfo::ColorBuffer*>> colorBufferInfosMapCache;
	std::unordered_map<std::string, RequiredBufferInfo::DepthStencilBuffer*> depthBufferInfoMapCache;

};

