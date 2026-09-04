#include "ResourceCreator.h"
#include "../../../../../Utility/StringConverter/StringConverter.h"

//外部
#include "../../../../Core/Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCmdLicences.h"
#include "../../../../Core/Device/DeviceContextCmds.h"

BufferContext::ResourceCreator::ResourceCreator(NexusFieldProof proof_, DeviceContextDiplomat* deviceContextDiplomat_)
{
	//生リソース生成コマンドを受け取る
	auto* cmdProvider = deviceContextDiplomat_->Access<DeviceContext::CommandProvider>();
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateResource> licence;

	createResourceCommand = cmdProvider->Provide<DeviceContextCmds::CreateResource>(licence);
}

BufferContext::ResourceCreator::~ResourceCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] BufferContext::ResourceCreator::ResourceContainer BufferContext::ResourceCreator::Create
(
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValuePtr_,
	D3D12_RESOURCE_STATES initialState_,
	const std::string& name_,
	int numResource_
)const
{
	ResourceContainer resourceContainer;

	for (int i = 0; i < numResource_; ++i)
	{
		//生リソース生成
		auto& resource = resourceContainer.emplace_back(createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, initialState_, name_));
		//生リソースに名を刻む
		resource->SetName(StringConverter::ConvertString(name_ + "[ " + std::to_string(i) + "]").c_str());
	}

	return std::move(resourceContainer);
}
