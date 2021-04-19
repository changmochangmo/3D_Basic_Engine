matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Diffuse;
float4 Color;


sampler2D BaseMap;

struct PS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
};

PS_INPUT vs_main(VS_INPUT input)
{
	PS_INPUT output;

	output.position.w = 1.0f;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	//°íÃÄ¾ßµÊ
	output.normal = input.normal;

	output.texcoord = input.texcoord;

	return output;
}

float4 ps_main(PS_INPUT input) : COLOR0
{
	float4 baseColor = tex2D(BaseMap, input.texcoord);
	return saturate(baseColor + Diffuse);
}

technique Default_Technique
{
	pass Default_Pass
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

};