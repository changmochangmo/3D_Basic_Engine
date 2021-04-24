//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// ColorShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string ColorShader_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

struct VS_INPUT 
{
   float4 Position : POSITION;
   
};

struct VS_OUTPUT 
{
   float4 Position : POSITION;
   
};

float4x4 matWorld : World;
float4x4 matView : View;
float4x4 matProj : Projection;


VS_OUTPUT ColorShader_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul(Input.Position, matWorld );
   Output.Position = mul(Output.Position, matView);
   Output.Position = mul(Output.Position, matProj);
   
   return Output;
   
}




float4 ColorShader_Pass_0_Pixel_Shader_ps_main() : COLOR
{   
   return( float4( 0.0f, 0.0f, 1.0f, 1.0f ) );   
}




//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique ColorShader
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 ColorShader_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 ColorShader_Pass_0_Pixel_Shader_ps_main();
   }

}

