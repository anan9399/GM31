#pragma once
#include"Bindable.h"
#include"renderer.h"
#include<vector>

class InputLayout : public Bindable
{
public:
	InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		const unsigned char* buffer,
		const long int fsize) 
	{
		Renderer::GetDevice()->CreateInputLayout(layout.data(),
			(UINT)layout.size(),
			buffer,
			fsize,
			m_pInputLayout.ReleaseAndGetAddressOf());
	}
	~InputLayout() = default;
	void Bind() noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};

