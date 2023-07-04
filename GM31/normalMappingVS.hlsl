#include "common.hlsl"



void main(in VS_IN_N In, out PS_IN_N Out)
{
    matrix wvp; //matrix型の変数wvpを定義する

	//wvp = ワールド変換行列×ビュー変換行列
    wvp = mul(World, View);
	//wvp = wvp × プロジェクション変換行列
    wvp = mul(wvp, Projection);

	//入力された頂点座標を変換して出力先へ代入する
    Out.Position = mul(In.Position, wvp);

	//入力されたUV座標を出力先へ代入する
    Out.TexCoord = In.TexCoord;


	//頂点の法線をワールド行列で変換する
    float4 worldNormal, normal;

	//Normal
    normal = float4(In.Normal.xyz, 0.0);
	//法線をワールド変換する
    worldNormal = mul(normal, World);
	//ワールド変換した法線を正規化する（拡大縮小の情報を削除する）
    Out.Normal = normalize(worldNormal);


	//頂点カラーはそのままコピー
    Out.Diffuse = In.Diffuse;

	//ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(In.Position, World);
	
    const float4 Tangent = float4(In.Tangent.xyz, 0.0f);
    Out.Tangent = normalize(mul(Tangent, World));
	
    const float4 Binormal = float4(In.Binormal.xyz, 0.0f);
    Out.Binormal = normalize(mul(Binormal, World));
}
