#include "Constants.hlsl"
#include "Util.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    uint4 boneIndices : BONEINDICES0;
    float4 boneWeights : BONEWEIGHTS0;
    float2 texCoord :TEXCOORD0;
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

    const float4 position = float4(vIn.position, 1.0);
    const float4 normal = float4(vIn.normal, 0.0);
    vIn.position = 0;
    vIn.normal = 0;

    for (int i = 0; i < 4; i++)
    {
        vIn.position += vIn.boneWeights[i] * mul(position, c_skinMatrix[vIn.boneIndices[i]]);
        vIn.normal += vIn.boneWeights[i] * mul(normal, c_skinMatrix[vIn.boneIndices[i]]);
    }

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

    pOut.diffuse = float4(DiffuseTexture.Sample(DefaultSampler, pIn.texCoord) * c_diffuseColor, c_specularPower);
    return pOut;
}

/*float4 PS(VOut pIn) : SV_TARGET
{
    pIn.normal = normalize(pIn.normal);
    float3 total = c_ambient;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
	    const PointLightData light = c_pointLight[i];
        if (light.isEnabled)
        {
            float3 diffuse;
            float3 specular;

            float3 directionToLight = light.position - pIn.worldPosition;

            float lenToLight = length(directionToLight);
            float smooth = smoothstep(-light.outerRadius, -light.innerRadius, -lenToLight);

            directionToLight = normalize(directionToLight);
	        {
                diffuse = c_diffuseColor * Safe_Dot(pIn.normal, directionToLight);
                diffuse = diffuse * light.lightColor;
	        }
	        {
                float3 reflection = reflect(-directionToLight, pIn.normal); //direction already normalized
                float3 directionToViewer = c_cameraPosition - pIn.worldPosition;
                directionToViewer = normalize(directionToViewer);
            	specular = pow(Safe_Dot(directionToViewer, reflection), c_specularPower);
                specular *= c_specularColor * light.lightColor;
            }

            total += (specular + diffuse) * smooth;
        }
    }
    float3 textureColor = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord);
    total = total * textureColor;
    return float4(clamp(total, 0, 1), 1.0);
}*/
