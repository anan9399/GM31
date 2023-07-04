#include "Field.h"
#include "renderer.h"


void Field::Init()
{
	int yoko = 20;//横のポリゴンの分割数
	int tate = 20;//縦のポリゴンの分割数
	float takasa = 0.0f;//ランダムで作成する高さの最大値
	float sizeX = 5.0f;//ポリゴンの横幅
	float sizeZ = 5.0f;//ポリゴンの高さ

	//必要な頂点数を計算する
	m_numVertex = (yoko + 1) * (tate + 1);
	m_numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D_N) * m_numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * m_numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_IndexBuffer);

	{//頂点バッファの中身を埋める

		// 頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_N* pVtx = (VERTEX_3D_N*)msr.pData;

		for (int y = 0; y < (tate + 1); y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				int i = y * (yoko + 1) + x;

				float height = ((float)rand() / RAND_MAX) * takasa;
				// 頂点座標の設定
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * sizeX + x * sizeX, height, (tate / 2.0f) * sizeZ - y * sizeZ);
				// UV値の設定
				pVtx[i].TexCoord = D3DXVECTOR2((float)x, (float)y);

				// 法線の設定
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
				D3DXVec3Cross(&pVtx[i].Tangent, &pVtx[i].Normal, &vUp);
				D3DXVec3Cross(&pVtx[i].Binormal, &pVtx[i].Normal, &pVtx[i].Tangent);

				// 頂点カラーの設定
				pVtx[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
	}

	{//インデックスバッファの中身を埋める

		// インデックスバッファのポインタを取得
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

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/brick_wall_diffuse.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/brick_wall_normal.jpg",
		NULL,
		NULL,
		&m_TextureNormal,
		NULL);
	assert(m_TextureNormal);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShaderN(&m_pVertexShader, &m_pInputLayout, "normalMappingVS.cso");
	Renderer::CreatePixelShader(&m_pPixelShader, "normalMappingPS.cso");

}


void Field::Uninit()
{



	//ここにシェーダーオブジェクトの解放を追加

}


void Field::Update()
{


}


void Field::Draw()
{


	//ここにシェーダー関連の描画準備を追加

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D_N);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	
	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, m_Texture.GetAddressOf());
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, m_TextureNormal.GetAddressOf());
	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);




	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);


	// ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed(m_numIndex, 0, 0);

}