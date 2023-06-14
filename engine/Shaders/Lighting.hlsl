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
    output.position = float4(vIn.position, 1.0);
    output.texCoord = vIn.texCoord;

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    float4 diffuseFromTexture = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord);
    if (diffuseFromTexture.a == 0)
    {
        return float4(diffuseFromTexture.rgb, 1.0f);

    }

    float4 normalFromTexture = NormalTexture.Sample(DefaultSampler, pIn.texCoord);
    float4 worldPosFromTexture = WorldPosTexture.Sample(DefaultSampler, pIn.texCoord);

    float3 total = c_ambient * diffuseFromTexture.rgb;

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
	    const PointLightData light = c_pointLight[i];
        if (light.isEnabled)
        {
            float3 diffuse;
            float3 specular;

            float3 directionToLight = light.position - worldPosFromTexture;

            float lenToLight = length(directionToLight);
            float smooth = smoothstep(-light.outerRadius, -light.innerRadius, -lenToLight);

            directionToLight = normalize(directionToLight);
	        {
                diffuse = c_diffuseColor * Safe_Dot(normalFromTexture.rgb, directionToLight);
                diffuse = diffuse * light.lightColor;
	        }
	        {
                float3 reflection = reflect(-directionToLight, normalFromTexture.rgb); //direction already normalized
                float3 directionToViewer = c_cameraPosition - worldPosFromTexture;
                directionToViewer = normalize(directionToViewer);
            	specular = pow(Safe_Dot(directionToViewer, reflection), diffuseFromTexture.a);
                specular *= light.lightColor;
            }

            total += (specular + diffuse) * smooth;
        }
    }
    return float4(clamp(total, 0, 1), 1.0);
    //return DiffuseTexture.Sample(DefaultSampler, pIn.texCoord) * pIn.color;
    //return float4(c_pointLight[1].lightColor, 1.0);
}
