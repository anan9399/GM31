
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN_N In, out float4 outDiffuse : SV_Target)
{
	//ノーマルマップテクスチャから色をサンプリングする
	//このピクセルの法線マップのデータRGBA値を取得
    float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
	//スケーリングして色→ベクトルデータへ変換する
    normalMap = normalMap * 2.0 - 1.0;

    float4 normal;
    normal.w = 0.0;
	
    const float3x3 tanToTarget = float3x3(
	    normalize(In.Tangent.xyz),
	    normalize(In.Binormal.xyz),
	    normalize(In.Normal.xyz)
	);
	
    normal.xyz = normalize(mul(normalMap.xyz, tanToTarget));

	//光源の向きと回転済みの法線とで内積を計算し、符号を反転して輝度を求める
    float light = -dot(Light.Direction.xyz, normal.xyz);
	//飽和演算(0.0～1.0の値にクランプする)
    light = saturate(light);

	//テクスチャから色をサンプリングする
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	//テクスチャの色に輝度を乗算する
    outDiffuse.rgb *= light;
	//透明度は輝度に影響しないのでそのまま使う
    outDiffuse.a *= In.Diffuse.a;


	////ブリンフォン鏡面反射
	////視線ベクトルを作成する（カメラからピクセルへ向かうベクトル）
 //   float3 evev = In.WorldPosition.xyz - CameraPosition.xyz;
 //   evev = normalize(evev);
	////ハーフベクトルを作成する（視線ベクトル＋ライトベクトル）
 //   float3 halfv = evev + Light.Direction.xyz;
 //   halfv = normalize(halfv);

 //   float specular = -dot(halfv, normal.xyz);
 //   saturate(specular);
 //   specular = pow(specular, 30);
 //   outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
}
