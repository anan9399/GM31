#include "Shadow.h"
#include "renderer.h"
#include"BindableBase.h"
#include"Bindable.h"
void Shadow::Init()
{
	int yoko = 1;//���̃|���S���̕�����
	int tate = 1;//�c�̃|���S���̕�����
	float takasa = 0.0f;//�����_���ō쐬���鍂���̍ő�l
	float sizeX = 2.0f;//�|���S���̉���
	float sizeZ = 2.0f;//�|���S���̍���

	//�K�v�Ȓ��_�����v�Z����
	m_numVertex = (yoko + 1) * (tate + 1);
	m_numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D_N) * m_numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * m_numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_IndexBuffer);

	{//���_�o�b�t�@�̒��g�𖄂߂�

		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_N* pVtx = (VERTEX_3D_N*)msr.pData;

		for (int y = 0; y < (tate + 1); y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				int i = y * (yoko + 1) + x;

				float height = ((float)rand() / RAND_MAX) * takasa;
				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * sizeX + x * sizeX, height, (tate / 2.0f) * sizeZ - y * sizeZ);
				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2((float)x, (float)y);

				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
				D3DXVec3Cross(&pVtx[i].Tangent, &pVtx[i].Normal, &vUp);
				D3DXVec3Cross(&pVtx[i].Binormal, &pVtx[i].Normal, &pVtx[i].Tangent);

				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_IndexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < tate; y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (yoko + 1) * y;
				idx++;
			}

			if (y < (tate - 1))
			{
				pIdx[idx] = yoko + (yoko + 1) * y;
				idx++;
				pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
				idx++;
			}
		}

		Renderer::GetDeviceContext()->Unmap(m_IndexBuffer.Get(), 0);
	}


	m_binds.emplace_back(Texture::Resolve("asset/texture/shadow.png", 0));

	auto pvs = VertexShader::Resolve("unlitTextureVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	m_binds.emplace_back(std::move(pvs));

	m_binds.emplace_back(std::make_shared<InputLayout>(layoutN, "layout", buffer, fsize));
	m_binds.emplace_back(PixelShader::Resolve("unlitTexturePS.cso"));

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}


void Shadow::Uninit()
{

	m_binds.clear();

}


void Shadow::Update()
{


}


void Shadow::Draw()
{


	//�����ɃV�F�[�_�[�֘A�̕`�揀����ǉ�

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D_N);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	for (auto& b : m_binds)
	{
		b->Bind();
	}

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// �|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed(m_numIndex, 0, 0);

}