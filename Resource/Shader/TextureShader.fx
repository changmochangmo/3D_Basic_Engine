matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Diffuse;
float4 Color;

texture baseTex;
sampler temp = sampler_state
{
	Texture = (baseTex);
};

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
	float4 baseColor = tex2D(temp, input.texcoord);
	float4 c = saturate(baseColor + Diffuse);
	c.a = 0.5;
	return c;
}

technique Default_Technique
{
	pass Default_Pass
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

};