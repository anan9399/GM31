
#include "common.hlsl"


Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	
	
    float4 dTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
    clip(dTex.a < 0.1f ? -1 : 1);
    outDiffuse = dTex;
    outDiffuse *= In.Diffuse * Material.Diffuse;

}
