
#include "main.h"
#include "renderer.h"
#include "meshField.h"



float g_FieldHeight[21][21] = 
{
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,3.0f,5.0f,7.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,3.0f,5.0f,5.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,3.0f,3.0f,4.0f,3.0f,3.0f,3.0f,3.0f,5.0f,3.0f,3.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,2.0f,2.0f,3.0f,2.0f,2.0f,2.0f,3.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,2.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,2.0f,1.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,3.0f,1.0f,0.0f,3.0f,3.0f,3.0f,4.0f,9.0f},
	{1.0f,6.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,-2.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,2.0f,4.0f,3.0f,5.0f,8.0f,8.0f},
	{6.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,-1.0f,-2.0f,-1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,3.0f,5.0f,8.0f,8.0f,9.0f},
	{1.0f,6.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,-2.0f,-2.0f,-1.0f,0.0f,0.0f,0.0f,2.0f,0.0f,3.0f,3.0f,7.0f,9.0f,10.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,3.0f,3.0f,5.0f,8.0f,7.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,2.0f,1.0f,1.0f,0.0f,3.0f,3.0f,3.0f,5.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,1.0f,0.0f,0.0f,1.0f,2.0f,2.0f,2.0f,1.0f,2.0f,5.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,9.0f,8.0f,7.0f,4.0f,3.0f,0.0f,0.0f,1.0f,0.0f,0.0f,2.0f,2.0f,2.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,9.0f,8.0f,5.0f,4.0f,3.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,10.0f,9.0f,5.0f,4.0f,3.0f,0.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,2.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,8.0f,8.0f,5.0f,4.0f,3.0f,0.0f,0.0f,1.0f,0.0f,-1.0f,-2.0f,-1.0f,0.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,0.0f,0.0f,0.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
	{1.0f,7.0f,6.0f,5.0f,4.0f,3.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,3.0f,3.0f,3.0f,4.0f,5.0f},
};


void MeshField::Init()
{

	// ���_�o�b�t�@����
	{
		for (int x = 0; x <= 20; x++)
		{
			for (int z = 0; z <= 20; z++)
			{
				m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, g_FieldHeight[x][z], (z - 10) * -5.0f);
				m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
				m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
			}
		}


	
		for (int x = 1; x <= 19; x++) {
			for (int z = 1; z <= 19; z++) {
				D3DXVECTOR3 vx, vz, vn;
				vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
				vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

				D3DXVec3Cross(&vn, &vz,&vx);
				D3DXVec3Normalize(&vn, &vn);
				m_Vertex[x][z].Normal = vn;

			}
		}


		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}




	// �C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[(22 * 2) * 20 - 2 ];

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)
				break;

			//�k�ރ|���S��
			index[i] = (x + 1) * 21 + 20;
			i++;

			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}




	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
											"asset/texture/brick_wall_diffuse.jpg",
											NULL,
											NULL,
											&m_Texture,
											NULL);
	assert( m_Texture );


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");


}


void MeshField::Uninit()
{

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}


void MeshField::Update()
{

}


void MeshField::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// �C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer( m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	material.TextureEnable = true;
	Renderer::SetMaterial( material );

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// �|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);

}
