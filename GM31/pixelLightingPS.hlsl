
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN_N In, out float4 outDiffuse : SV_Target)
{
	//�@���𐳋K�����Ċi�[����
	float4 normal = normalize(In.Normal);

	//�����o�[�g
    float light = -dot(Light.Direction.xyz, normal.xyz);
    light = saturate(light);

	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= light;
    outDiffuse.a *= In.Diffuse.a;
   
    float4 color;
    color = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
    color += In.Diffuse * Material.Ambient * Light.Ambient;
    color += Material.Emission;
    color.a = In.Diffuse.a * Material.Diffuse.a;
    outDiffuse *= color;
	
	
	//�u�����t�H�����ʔ���
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 halfv = eyev + Light.Direction.xyz;
    halfv = normalize(halfv);

    float specular = -dot(halfv, normal.xyz);
    saturate(specular);
    specular = pow(specular,256);
    outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
}
