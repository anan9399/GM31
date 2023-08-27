#include "IndexBuffer.h"
#include"BindableCodex.h"

IndexBuffer::IndexBuffer(const char* tag, MODEL& model)
	:
	m_tag(tag)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * model.IndexNum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = model.IndexArray;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
}

void IndexBuffer::Bind() noexcept
{
	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Resolve(const char* tag, MODEL& model)
{
	return Codex::Resolve<IndexBuffer>( tag,model);
}

std::string IndexBuffer::GetUID() const noexcept
{
	return GenerateUID_(m_tag);
}

std::string IndexBuffer::GenerateUID_(const std::string& tag)
{
	using namespace std::string_literals;
	return typeid(IndexBuffer).name() + "#"s + tag;
}
