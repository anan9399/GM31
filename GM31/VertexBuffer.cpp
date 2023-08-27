#include "VertexBuffer.h"
#include"BindableCodex.h"

VertexBuffer::VertexBuffer(const char* tag, MODEL& model)
	:
	m_tag(tag)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * model.VertexNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = model.VertexArray;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	
}

void VertexBuffer::Bind() noexcept
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Resolve(const char* tag, MODEL& model)
{
	return Codex::Resolve<VertexBuffer>(tag, model);
}

std::string VertexBuffer::GetUID() const noexcept
{
	return GenerateUID_(m_tag);
}

std::string VertexBuffer::GenerateUID_(const std::string& tag)
{
	using namespace std::string_literals;
	return typeid(VertexBuffer).name() + "#"s + tag;
}
