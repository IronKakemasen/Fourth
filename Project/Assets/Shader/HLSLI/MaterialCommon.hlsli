#pragma once

#include "../../Shared/Material.h"
#include "../../Shared/ConstantBuffers.h"


MaterialStandard LoadMaterialStandard(uint materialID_)
{
    StructuredBuffer<MaterialArrBufferSrvIndexGroup> srvGroupBuffer =
        ResourceDescriptorHeap[gMaterialArrBufferSrvIndicesSrvIndex];

    StructuredBuffer<MaterialIndexGroup> indexGroupArr =
        ResourceDescriptorHeap[gMaterialIDGroupArrBufferSrv];

    StructuredBuffer<MaterialStandard> standardArr =
        ResourceDescriptorHeap[srvGroupBuffer[0].standardSrv];

    MaterialIndexGroup indexGroup = indexGroupArr[materialID_];

    return standardArr[indexGroup.standardIndex];
}

MaterialGridLine LoadMaterialGridLine(uint materialID_)
{
    StructuredBuffer<MaterialArrBufferSrvIndexGroup> srvGroupBuffer =
        ResourceDescriptorHeap[gMaterialArrBufferSrvIndicesSrvIndex];

    StructuredBuffer<MaterialIndexGroup> indexGroupArr =
        ResourceDescriptorHeap[gMaterialIDGroupArrBufferSrv];

    StructuredBuffer<MaterialGridLine> gridLineArr =
        ResourceDescriptorHeap[srvGroupBuffer[0].gridLineSrv];

    MaterialIndexGroup indexGroup = indexGroupArr[materialID_];

    return gridLineArr[indexGroup.gridLineIndex];
}

