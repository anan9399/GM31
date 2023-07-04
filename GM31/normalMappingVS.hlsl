#include "common.hlsl"



void main(in VS_IN_N In, out PS_IN_N Out)
{
    matrix wvp; //matrix�^�̕ϐ�wvp���`����

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

	//Normal
    normal = float4(In.Normal.xyz, 0.0);
	//�@�������[���h�ϊ�����
    worldNormal = mul(normal, World);
	//���[���h�ϊ������@���𐳋K������i�g��k���̏����폜����j
    Out.Normal = normalize(worldNormal);


	//���_�J���[�͂��̂܂܃R�s�[
    Out.Diffuse = In.Diffuse;

	//���[���h�ϊ��������_���W���o��
    Out.WorldPosition = mul(In.Position, World);
	
    const float4 Tangent = float4(In.Tangent.xyz, 0.0f);
    Out.Tangent = normalize(mul(Tangent, World));
	
    const float4 Binormal = float4(In.Binormal.xyz, 0.0f);
    Out.Binormal = normalize(mul(Binormal, World));
}
