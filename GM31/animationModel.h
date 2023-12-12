#pragma once

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp-vc143-mt.lib")

#define NUM_BONES_PER_VERTEX 10000

//�ό`�㒸�_�\����
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;
	int				BoneNum;
	std::string		BoneName[4];//�{���̓{�[���C���f�b�N�X�ŊǗ�����ׂ�
	float			BoneWeight[4];
};

//�{�[���\����
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};


//�{�[���\����
struct BONE_TEST{
	bool isSkinned = false;
	int parentIndex;
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};


struct BONEDATA {
	UINT boneIndex[NUM_BONES_PER_VERTEX];
	float weights[NUM_BONES_PER_VERTEX];
	void Add(UINT boneID, float weight) {
		for (size_t i = 0; i < NUM_BONES_PER_VERTEX; i++) {
			if (weights[i] == 0.0f) {
				boneIndex[i] = boneID;
				weights[i] = weight;
				return;
			}
		}
		//insert error program
		//MessageBox(NULL, L"bone index out of size", L"Error", NULL);
	}
};

class AnimationModel
{
private:
	const aiScene* m_AiScene = nullptr;
	std::unordered_map<std::string, const aiScene*> m_Animation;

	ID3D11Buffer**	m_VertexBuffer;
	ID3D11Buffer**	m_IndexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;//�ό`�㒸�_�f�[�^
	std::unordered_map<std::string, BONE> m_Bone;//�{�[���f�[�^�i���O�ŎQ�Ɓj

	std::unordered_map<std::string, int> m_BoneMapping;//�{�[���f�[�^�C���f�b�N�X�i���O�ŎQ�Ɓj
	//std::vector<BoneData> vertexBoneData(mesh->mNumVertices);
	std::vector<BONE_TEST> m_Bones;//�{�[���f�[�^�i�j

	void CreateBone(aiNode* Node,int parenIndex);
	void UpdateBoneMatrix(aiNode* Node, aiMatrix4x4 Matrix);

public:
	void Load( const char *FileName );
	void LoadBone(const aiMesh* mesh,std::vector<BONEDATA> boneData	);
	void LoadAnimation( const char *FileName, const char *Name );
	void Unload();

	//void Update(const char *AnimationName, int Frame);
	void Update(const char *AnimationName1, int Frame1, 
				const char* AnimationName2, int Frame2,float BlendState );
	void Draw();
};