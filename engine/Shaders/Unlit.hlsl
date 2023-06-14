#include "Constants.hlsl"
#include "Util.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 texCoord : TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float4 worldPosition : WORLDPOSITION;
};

VOut VS(VIn vIn)
{
    VOut output;
    output.worldPosition = mul(float4(vIn.position, 1.0), c_modelToWorld);
    output.position = mul(output.worldPosition, c_viewProj);
    output.normal = mul(float4(vIn.normal, 0.0), c_modelToWorld);
    output.texCoord = vIn.texCoord;

    return output;
}

POut PS(VOut pIn) : SV_TARGET
{
    POut pOut;
    pOut.normal = float4(normalize(pIn.normal), 0.0);
    pOut.worldPos = pIn.worldPosition;

    pOut.diffuse = float4(DiffuseTexture.Sample(DefaultSampler, pIn.texCoord).rgb, 0);
    return pOut;
}

// float4 PS(VOut pIn) : SV_TARGET
// {
//     float3 textureColor = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord);
//     return float4(textureColor, 1.0);
// }
