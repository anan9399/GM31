#include "common.hlsl"


struct ANIMATE
{
	matrix inMatrix[4];
	float   BoneWeight[4];
};

cbuffer AnimateBuffer : register(b6)
{
	ANIMATE Animation;

}


void main(in VS_IN In, out PS_IN_N Out)
{


    float4x4 skinTransform = float4x4(1.0f, 0.0f, 0.0f, 0.0f,
		                               0.0f, 1.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 1.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 1.0f);

 
    skinTransform += Animation.inMatrix[0] * Animation.BoneWeight[0];
    skinTransform += Animation.inMatrix[1] * Animation.BoneWeight[1];
    skinTransform += Animation.inMatrix[2] * Animation.BoneWeight[2];
    skinTransform += Animation.inMatrix[3] * Animation.BoneWeight[3];
	
    float worldPos; //matrix型の変数wvpを定義する
    worldPos = mul(skinTransform, In.Position);
	
    worldPos = mul(worldPos, World);
	//wvp = ワールド変換行列×ビュー変換行列
    worldPos = mul(worldPos, View);
	//wvp = wvp × プロジェクション変換行列
    worldPos = mul(worldPos, Projection);

	// 法線ベクトルを変換
    float3 transNormal = mul((float3x3) skinTransform, In.Normal.xyz);
    float3 worldNormal = mul((float3x3) World, transNormal);

	
	//入力された頂点座標を変換して出力先へ代入する
    Out.Position = worldPos;

	//入力されたUV座標を出力先へ代入する
    Out.TexCoord = In.TexCoord;
	
		
	

    Out.Normal = float4(normalize(worldNormal), 0.0f);
	Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
	Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);


	//頂点カラーはそのままコピー
	Out.Diffuse = In.Diffuse;
	

	Out.WorldPosition = mul(In.Position, World);
}
