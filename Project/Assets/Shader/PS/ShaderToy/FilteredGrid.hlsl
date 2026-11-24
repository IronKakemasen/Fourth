#include "../../HLSLI/MaterialCommon.hlsli"
#include "../../HLSLI/CameraCommon.hlsli"


//ーーーシェーダートイで公開されていたグリッド描画コードをAIに再構築してもらいましたーーー

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


float gridIntegral(float x, float lineWidth)
{
    float cell = floor(x);
    float f = frac(x);

    float halfWidth = lineWidth * 0.5;

    float localArea =
        min(f, halfWidth) +
        max(f - (1.0 - halfWidth), 0.0);

    return cell * lineWidth + localArea;
}

// ========================================
// 1方向のグリッド線のカバレッジ
// ========================================

float gridCoverage1D(
    float p,
    float pixelWidth,
    float lineWidth
)
{
    pixelWidth = max(pixelWidth, 0.000001);
    lineWidth = clamp(lineWidth, 0.0001, 0.99);

    float a = p - pixelWidth * 0.5;
    float b = p + pixelWidth * 0.5;

    return saturate(
        (gridIntegral(b, lineWidth) -
         gridIntegral(a, lineWidth)) / pixelWidth
    );
}

// ========================================
// Pixel Shader
// ========================================

float4 main(PSInput input) : SV_Target
{
    MaterialGridLine materialGridLine =
        LoadMaterialGridLine(gMaterialID);

    float2 p = input.worldPosition.xz;

    float2 dx = ddx(p);
    float2 dy = ddy(p);

    float2 fw = max(
        abs(dx) + abs(dy),
        float2(1e-6, 1e-6)
    );

    CameraData srcCamera = AccessCamera(0);

    float cameraDistance = length(
        input.worldPosition - srcCamera.worldPos.xyz
    );

    const float fadeStart = 15.0;
    const float fadeEnd = 65.0;

    float distanceFade =
        1.0 - smoothstep(fadeStart, fadeEnd, cameraDistance);

    // Fine Grid
    const float fineWidth = 0.035;

    float fineCoverageX =
        gridCoverage1D(p.x, fw.x, fineWidth);

    float fineCoverageZ =
        gridCoverage1D(p.y, fw.y, fineWidth);

    float fineLODX =
        1.0 - smoothstep(0.20, 0.65, fw.x);

    float fineLODZ =
        1.0 - smoothstep(0.20, 0.65, fw.y);

    float fineAlphaX = fineCoverageX * fineLODX;
    float fineAlphaZ = fineCoverageZ * fineLODZ;

    float fineAlpha =
        1.0 - (1.0 - fineAlphaX) * (1.0 - fineAlphaZ);

    // Major Grid (5m)
    const float majorInterval = 5.0;
    const float majorWidth = 0.075;

    float majorCoverageX = gridCoverage1D(
        p.x / majorInterval,
        fw.x / majorInterval,
        majorWidth / majorInterval
    );

    float majorCoverageZ = gridCoverage1D(
        p.y / majorInterval,
        fw.y / majorInterval,
        majorWidth / majorInterval
    );

    float majorLODX =
        1.0 - smoothstep(0.8, 2.5, fw.x);

    float majorLODZ =
        1.0 - smoothstep(0.8, 2.5, fw.y);

    float majorAlphaX = majorCoverageX * majorLODX;
    float majorAlphaZ = majorCoverageZ * majorLODZ;

    float majorAlpha =
        1.0 - (1.0 - majorAlphaX) * (1.0 - majorAlphaZ);

    // Background and Grid Color
    float3 backgroundColor =
        materialGridLine.backgroundColor.rgb;

    float3 gridColor =
        materialGridLine.gridColor.rgb;

    float3 color = lerp(
        backgroundColor,
        gridColor,
        fineAlpha * distanceFade
    );

    float3 majorColor = float3(0.52, 0.43, 0.28);

    color = lerp(
        color,
        majorColor,
        majorAlpha * distanceFade * 0.8
    );

    // X Axis: Red / Z Axis: Green
    const float axisWidth = 0.055;

    float axisX = 1.0 - smoothstep(
        axisWidth * 0.5 - fw.y * 0.5,
        axisWidth * 0.5 + fw.y * 0.5,
        abs(p.y)
    );

    float axisZ = 1.0 - smoothstep(
        axisWidth * 0.5 - fw.x * 0.5,
        axisWidth * 0.5 + fw.x * 0.5,
        abs(p.x)
    );

    float3 xAxisColor = float3(0.65, 0.28, 0.27);
    float3 zAxisColor = float3(0.28, 0.52, 0.36);
    
    axisX *= distanceFade;
    axisZ *= distanceFade;

    color = lerp(color, xAxisColor, axisX);
    color = lerp(color, zAxisColor, axisZ);

    return float4(color, 1.0);
}