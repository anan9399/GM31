#include "Score.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"
#include"manager.h"
#include"Finish.h"
void Score::Init()
{

	VERTEX_3D vertex[4];

	


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/number.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);




	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "unlitTexturePS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "unlitTextureVS.cso");


	//AddComponent<Sprite>()->Init("asset\\texture\\number.png", m_Position, 300.0f, 300.0f);
	
	
	//m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);

}


void Score::Uninit()
{
	//ここにシェーダーオブジェクトの解放を追加
	GameObject::Uninit();
}


void Score::Update()
{
	GameObject::Update();
	
}


void Score::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//ここにシェーダー関連の描画準備を追加
	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, m_Texture.GetAddressOf());

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	int count = m_count;

	for (int i = 0; i < 3; i++)
	{
		//頂点座標の算出
		float vx = 100.0 - i * 30.0f;
		float vy = 30.0f;
		float height = 50.0f;
		float width = 50.0f;

		int num = count % 10;
		count /= 10;
		float x = num % 5 * (1.0f / 5.0f);
		float y = num / 5 * (1.0f / 5.0f);



		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer.Get(), 0
			, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(vx, vy, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(vx + width, vy, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + 0.2f, y);

		vertex[2].Position = D3DXVECTOR3(vx, vy + height, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.2f);

		vertex[3].Position = D3DXVECTOR3(vx + width, vy + height, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + 0.2f, y + 0.2f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);






		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);

		//GameObject::Draw();
	}


}