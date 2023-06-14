#include "Constants.hlsl"
#include "Util.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float4 color : COLOR0;
    float2 texCoord :TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
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
    output.color = vIn.color;
    output.texCoord = vIn.texCoord;

    return output;
}

float3 GetLight(VOut pIn)
{
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
    return total;
}

float4 PS(VOut pIn) : SV_TARGET
{
    pIn.normal = normalize(pIn.normal);
    float3 total = GetLight(pIn);
    float3 textureColor = DiffuseTexture.Sample(DefaultSampler, pIn.texCoord);
    total = total * textureColor * pIn.color;
    return float4(clamp(total, 0, 1), 1.0);
}
