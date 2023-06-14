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
    float4 textureColor = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord);
    if(textureColor.r >= 0.8 || textureColor.g >= 0.8 || textureColor.b >=0.8)
    {
        return textureColor;
    }
    return 0.0;
}
