#include "common.hlsl"


struct ANIMATE
{
	matrix inMatrix[4];
	float	BoneWeight[4];
};

cbuffer AnimateBuffer : register(b6)
{
	ANIMATE Animation;

}


void main(in VS_IN In, out PS_IN_N Out)
{
	matrix wvp;//matrix�^�̕ϐ�wvp���`����

	//wvp = ���[���h�ϊ��s��~�r���[�ϊ��s��
	wvp = mul(World, View);
	//wvp = wvp �~ �v���W�F�N�V�����ϊ��s��
	wvp = mul(wvp, Projection);

	//���͂��ꂽ���_���W��ϊ����ďo�͐�֑������
	Out.Position = mul(In.Position, wvp);

	//���͂��ꂽUV���W���o�͐�֑������
	Out.TexCoord = In.TexCoord;

	//���_�̖@�������[���h�s��ŕϊ�����
	float4 worldNormal, normal;

	

	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal;
	Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
	Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);

	matrix outMatrix[4];
	outMatrix[0] = Animation.inMatrix[0];

	//���_�J���[�͂��̂܂܃R�s�[
	Out.Diffuse = In.Diffuse;
	

	Out.WorldPosition = mul(In.Position, World);
}
