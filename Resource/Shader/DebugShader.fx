matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Color;

struct PS_INPUT
{
	float4 position : POSITION;
};

struct VS_INPUT
{
	float4 position : POSITION;
};

PS_INPUT vs_main(VS_INPUT input)
{
	PS_INPUT output;

	output.position.w = 1.0f;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);


	return output;
}

float4 ps_main(PS_INPUT input) : COLOR0
{
	float4 baseColor = Color;
	return baseColor;
}

technique Default_Technique
{
	pass Default_Pass
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

};