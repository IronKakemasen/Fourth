#pragma once
#include "../ModelContext.h"
#include "../ModelContextCmds.h"


class ModelContext::ModelContainer
{
public:

	struct Local_AddLicence;

	ModelContainer(NexusFieldProof proof_);
	~ModelContainer();

	void Add(Local_AddLicence addLicence_,std::unique_ptr<Model>&& model_);

	//コンテナの中身をっ見るためのコマンド
	ModelContextCmds::WatchModelContainer WatchDataCmd(ProviderKey key_)const;

private:

	std::vector<std::unique_ptr<Model>> container;

};

struct ModelContext::ModelContainer::Local_AddLicence
{
private:

	friend class ModelContext::ModelCreator;
	explicit Local_AddLicence() = default;
};



