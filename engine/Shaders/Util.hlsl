float Safe_Dot(float3 a, float3 b)
{
    return max(0, dot(a, b));
}

struct POut
{
    float4 diffuse : SV_TARGET0;
    float4 normal : SV_TARGET1;
    float4 worldPos : SV_TARGET2;
};