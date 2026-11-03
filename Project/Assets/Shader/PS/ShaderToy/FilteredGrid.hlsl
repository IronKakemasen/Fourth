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




cbuffer GridConstants : register(b0)
{
    float4 GridColor;
    float4 BackgroundColor;

    float GridScale;
    float GridRatio;
    float2 Padding;
};

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

// ShaderToy original analytic grid filtering
float gridTextureGradBox(
    float2 p,
    float2 ddxUV,
    float2 ddyUV)
{
    float2 w = max(abs(ddxUV), abs(ddyUV)) + 0.01;

    float2 a = p + 0.5 * w;
    float2 b = p - 0.5 * w;

    float2 i =
        (
            floor(a) + min(frac(a) * GridRatio, 1.0)
            - floor(b) - min(frac(b) * GridRatio, 1.0)
        ) / (GridRatio * w);

    return (1.0 - i.x) * (1.0 - i.y);
}

// Pixel Shader
float4 PSMain(PSInput input) : SV_Target
{
    float2 uv = input.uv * GridScale;

    float2 dx = ddx(uv);
    float2 dy = ddy(uv);

    float grid = gridTextureGradBox(uv, dx, dy);

    float3 color = lerp(
        BackgroundColor.rgb,
        GridColor.rgb,
        grid
    );

    return float4(color, 1.0);
}
