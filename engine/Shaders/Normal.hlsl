#include "Constants.hlsl"
#include "Util.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float3 tangent : TANGENT0;
    float2 texCoord :TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 worldPosition : WORLDPOSITION;
};

VOut VS(VIn vIn)
{
    VOut output;
    output.worldPosition = mul(float4(vIn.position, 1.0), c_modelToWorld);
    output.position = mul(output.worldPosition, c_viewProj);
    output.normal = mul(float4(vIn.normal, 0.0), c_modelToWorld);
    output.texCoord = vIn.texCoord;
    output.tangent = mul(float4(vIn.tangent, 0.0), c_modelToWorld);
    return output;
}

POut PS(VOut pIn) : SV_TARGET
{
    pIn.normal = normalize(pIn.normal);
    pIn.tangent = normalize(pIn.tangent);
    float3 bitangent = cross(pIn.normal, pIn.tangent);
    float3x3 tangentToWorld = float3x3(pIn.tangent, bitangent, pIn.normal);
    float3 normalFromMap = NormalTexture.Sample(DefaultSampler, pIn.texCoord);
    normalFromMap = normalFromMap * 2 - 1.0; // unbias
    normalFromMap = mul(normalFromMap, tangentToWorld);

    POut pOut;
    pOut.normal = float4(normalize(normalFromMap), 0.0);
    pOut.worldPos = pIn.worldPosition;

    pOut.diffuse = float4(DiffuseTexture.Sample(DefaultSampler, pIn.texCoord) * c_diffuseColor, c_specularPower);
    return pOut;
}

/*float4 PS(VOut pIn) : SV_TARGET
{
    pIn.normal = normalize(pIn.normal);
    pIn.tangent = normalize(pIn.tangent);
    float3 bitangent = cross(pIn.normal, pIn.tangent);
    float3x3 tangentToWorld = float3x3(pIn.tangent, bitangent, pIn.normal);
    float3 normalFromMap = NormalTexture.Sample(DefaultSampler, pIn.texCoord);
    normalFromMap = normalFromMap * 2 - 1.0; // unbias
    normalFromMap = mul(normalFromMap, tangentToWorld);
    float3 total = c_ambient * c_diffuseColor;
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
                diffuse = c_diffuseColor * Safe_Dot(normalFromMap, directionToLight);
                diffuse = diffuse * light.lightColor;
	        }
	        {
                float3 reflection = reflect(-directionToLight, normalFromMap); //direction already normalized
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
