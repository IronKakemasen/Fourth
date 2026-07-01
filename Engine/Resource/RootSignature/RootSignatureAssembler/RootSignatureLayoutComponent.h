#pragma once


namespace RootSignatureLayoutComponent
{
    enum class ShaderStage
    {
        kAll,  
        kVS,   
        kHS,   
        kDS,   
        kGS,   
        kPS   
    };

    enum class SamplerState
    {
        PointWrap,          //ポイントサンプリング - 繰り返し
        PointClamp,         //ポイントサンプリング - クランプ
        LinearWrap,         //トライリニアサンプリング - 繰り返し
        LinearClamp,        //トライリニアサンプリング - クランプ
        AnisotropicWrap,    //異方性サンプリング - 繰り返し
        AnisotropicClamp,   //異方性サンプリング - クランプ
    };

}