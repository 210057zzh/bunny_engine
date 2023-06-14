#include "Constants.hlsl"
#include "Util.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float2 texCoord : TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

VOut VS(VIn vIn)
{
    VOut output;
    output.position = float4(vIn.position,1.0);
    output.texCoord = vIn.texCoord;

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    const float3 offset = float3(0.0, 1.3846153846, 3.2307692308);
    const float3 weight = float3(0.2270270270, 0.3162162162, 0.0702702703);

    float w;
    float h;
    DiffuseTexture.GetDimensions(w, h);

    float4 textureColor = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord) * weight[0];
    for (int i = 1; i < 3; i++)
    {
        textureColor += DiffuseTexture.Sample(DefaultSampler, pIn.texCoord + float2(0.0, offset[i] / h))
                * weight[i];
        textureColor += DiffuseTexture.Sample(DefaultSampler, pIn.texCoord - float2(0.0, offset[i] / h))
                * weight[i];
    }
    return textureColor;
}
