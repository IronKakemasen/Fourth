#include "PreCompileHedder.h"
#include "ViewCreatorBehavior.h"
#include "../DescriptorHeapClass/DescriptorHeapClass.h"

//namespace
//{
//	const std::string fileName = "ViewCreatorBehavior.cpp";
//}
//
//
//ViewCreatorBehavior::ViewCreatorBehavior(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
//	: descriptorHeapClass(descriptorHeapClass_)
//{
//
//}
//
//template<>
//[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE ViewCreatorBehavior::CalculateNextHandle()
//{
//	ErrorMessageOutput::Assert::DetectError
//	(
//		(currentCreateNum < descriptorHeapClass->kMaxDescriptor),
//		"もうこれ以上Viewを作れません", fileName
//	);
//
//	D3D12_CPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeapClass->descriptorHeap->GetCPUDescriptorHandleForHeapStart();
//	D3D12_CPU_DESCRIPTOR_HANDLE next;
//
//	next.ptr = handleStartCPU.ptr + descriptorHeapClass->handleIncrementSize * currentCreateNum;
//
//
//
//	return next;
//}
//
//template<>
//[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE ViewCreatorBehavior::CalculateNextHandle()
//{
//	ErrorMessageOutput::Assert::DetectError
//	(
//		(currentCreateNum < descriptorHeapClass->kMaxDescriptor),
//		"もうこれ以上Viewを作れません", fileName
//	);
//
//	D3D12_GPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeapClass->descriptorHeap->GetGPUDescriptorHandleForHeapStart();
//	D3D12_GPU_DESCRIPTOR_HANDLE next;
//
//	next.ptr = handleStartCPU.ptr + descriptorHeapClass->handleIncrementSize * currentCreateNum;
//
//	return next;
//}
//
//
