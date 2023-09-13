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
	
    float worldPos; //matrix�^�̕ϐ�wvp���`����
    worldPos = mul(skinTransform, In.Position);
	
    worldPos = mul(worldPos, World);
	//wvp = ���[���h�ϊ��s��~�r���[�ϊ��s��
    worldPos = mul(worldPos, View);
	//wvp = wvp �~ �v���W�F�N�V�����ϊ��s��
    worldPos = mul(worldPos, Projection);

	// �@���x�N�g����ϊ�
    float3 transNormal = mul((float3x3) skinTransform, In.Normal.xyz);
    float3 worldNormal = mul((float3x3) World, transNormal);

	
	//���͂��ꂽ���_���W��ϊ����ďo�͐�֑������
    Out.Position = worldPos;

	//���͂��ꂽUV���W���o�͐�֑������
    Out.TexCoord = In.TexCoord;
	
		
	

    Out.Normal = float4(normalize(worldNormal), 0.0f);
	Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
	Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);


	//���_�J���[�͂��̂܂܃R�s�[
	Out.Diffuse = In.Diffuse;
	

	Out.WorldPosition = mul(In.Position, World);
}
