cbuffer perspectiveObject : register(b0)
{
    float4x4 worldViewProj;
}

struct VertexInput
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct VertexOutput
{
    float4 posH : SV_Position;
    float4 color : COLOR;
};

VertexOutput TestVS(VertexInput ver)
{
    VertexOutput output;
    
    output.posH = mul(float4(ver.pos, 1.0f), worldViewProj);
    output.color = ver.color;
    
    return output;
}

float4 TestPS(VertexOutput input) : SV_Target
{
    return input.color;
}