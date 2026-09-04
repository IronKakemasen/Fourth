#pragma once
#include "DeviceContextCommandProvider.h"


class DescriptorHeapContext;
class BufferContext;
class CommandContext;
class SwapChainContext;
class RootSignatureContext;
class PSO_Context;

struct DeviceContext::CommandProvider::CreateResourceLicence
{
private:

	friend class BufferContext;
	explicit CreateResourceLicence() = default;
};

struct DeviceContext::CommandProvider::CreateViewLicence
{
private:

	friend class DescriptorHeapContext;
	explicit CreateViewLicence() = default;
};

struct DeviceContext::CommandProvider::CreateDescriptorHeapLicence
{
private:

	friend class DescriptorHeapContext;
	explicit CreateDescriptorHeapLicence() = default;
};

struct DeviceContext::CommandProvider::CreateSwapChainLicence
{
private:

	friend class SwapChainContext;
	explicit CreateSwapChainLicence() = default;
};

struct DeviceContext::CommandProvider::CreateRootSigLicence
{
private:

	friend class RootSignatureContext;
	explicit CreateRootSigLicence() = default;
};

struct DeviceContext::CommandProvider::CreatePSO_Licence
{
private:

	friend class PSO_Context;
	explicit CreatePSO_Licence() = default;
};



