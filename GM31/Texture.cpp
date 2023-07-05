#include "Texture.h"
#include "Surface.h"
#include"renderer.h"


	namespace wrl = Microsoft::WRL;

	Texture::Texture(const std::string& path, UINT slot)
		:
		m_path(path),
		m_slot(slot)
	{

		// load surface
		const auto s = Surface::FromFile(path);
		// create texture resource
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = s.GetWidth();
		textureDesc.Height = s.GetHeight();
		textureDesc.MipLevels = 0;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		// The more you bind, the less the program can be optimized
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		// TODO 1 use normal map to improve the accuracy of mipmap
		// TODO 2  Create a staging texture for mipmap first and then process it 
		//         before creating the final texture for only BIND_SHADER_RESOURCE
		wrl::ComPtr<ID3D11Texture2D> pTexture;
		Renderer::GetDevice()->CreateTexture2D(
			&textureDesc, nullptr, &pTexture
		);

		// write image data into top mip level
		Renderer::GetDeviceContext()->UpdateSubresource(
			pTexture.Get(), 0u, nullptr, s.GetBufferPtrConst(), s.GetWidth() * sizeof(Surface::Color), 0u
		);

		// create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;
		Renderer::GetDevice()->CreateShaderResourceView(
			pTexture.Get(), &srvDesc, &m_pTextureView
		);

		// generate the mip chain using the gpu rendering pipeline
		Renderer::GetDeviceContext()->GenerateMips(m_pTextureView.Get());
	}

	void Texture::Bind() noexcept
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(m_slot, 1u, m_pTextureView.GetAddressOf());
	}
