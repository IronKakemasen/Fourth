#include "../../HLSLI/MaterialCommon.hlsli"


//ーーーシェーダートイで公開されていたグリッド描画コードをAIに簡略化してもらいましたーーー

//https://www.shadertoy.com/view/XtBfzz

// The MIT License
// Copyright © 2017 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Analiyically filtering a grid pattern (ie, not using supersampling or mipmapping.
//
// Info: https://iquilezles.org/articles/filterableprocedurals
//  
// More filtered patterns:  https://www.shadertoy.com/playlist/l3KXR1


// --- analytically box-filtered grid ---



struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
    float3 worldPosition : POSITION0;

};


// 周期的なグリッド線の積分
float gridIntegral(float x, float lineWidth)
{
    float cell = floor(x);
    float f = frac(x);

    float halfWidth = lineWidth * 0.5;

    float local =
        min(f, halfWidth) +
        max(f - (1.0 - halfWidth), 0.0);

    return cell * lineWidth + local;
}

// Pixel Shader用グリッドフィルタ
float gridTextureGradBox(
    float2 p,
    float2 ddxUV,
    float2 ddyUV,
    float lineWidth
)
{
    float2 w = max(
        abs(ddxUV) + abs(ddyUV),
        0.000001
    );

    // ピクセルが覆う範囲
    float2 a = p - w * 0.5;
    float2 b = p + w * 0.5;

    // X方向の線のカバー率
    float coverageX =
        (gridIntegral(b.x, lineWidth) -
         gridIntegral(a.x, lineWidth)) / w.x;

    // Y方向の線のカバー率
    float coverageY =
        (gridIntegral(b.y, lineWidth) -
         gridIntegral(a.y, lineWidth)) / w.y;

    return saturate(max(coverageX, coverageY));
}

// Pixel Shader
float4 main(PSInput input) : SV_Target
{
    MaterialGridLine materialGridLine =
        LoadMaterialGridLine(gMaterialID);

    // ワールド座標のXZを使用
    float2 gridUV = input.worldPosition.xz;

    float2 dx = ddx(gridUV);
    float2 dy = ddy(gridUV);

    float grid = gridTextureGradBox(
        gridUV,
        dx,
        dy,
        materialGridLine.gridRatio
    );

    float3 color = lerp(
        materialGridLine.backgroundColor.rgb,
        materialGridLine.gridColor.rgb,
        grid
    );

    return float4(color, 1.0);
}