#pragma once
#include"Bindable.h"
#include"renderer.h"
#include<vector>
#include<string>
#include"VertexShader.h"
class InputLayout : public Bindable
{
public:
	InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const std::string& name,
		VertexShader& vs)
		:
		m_name(name)
	{
		
		Renderer::GetDevice()->CreateInputLayout(layout.data(),
			(UINT)layout.size(),
			vs.GetBuffer(),
			vs.Getfsize(),
			m_pInputLayout.ReleaseAndGetAddressOf());
	}

	InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const std::string& name,
		const unsigned char* buffer,
		const long int fsize)
		:
		m_name(name)
	{
		Renderer::GetDevice()->CreateInputLayout(layout.data(),
			(UINT)layout.size(),
			buffer,
			fsize,
			m_pInputLayout.ReleaseAndGetAddressOf());
	}

	~InputLayout() = default;
	void Bind() noexcept override;

	// Try to indicate by input name , but faild :(

	//static std::shared_ptr<InputLayout> Resolve(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const std::string& name, VertexShader& vs);
	//static std::string GenerateUID(const std::string& FileName, VertexShader& vs);
	//std::string GetUID() const noexcept override;

protected:
	std::string m_name;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};

