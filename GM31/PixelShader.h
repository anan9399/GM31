#pragma once
#include "Bindable.h"
#include"renderer.h"
#include<io.h>
#include<string>
class PixelShader : public Bindable
{
public:
	PixelShader(const char* FileName);
	void Bind() noexcept override;


	static std::shared_ptr<PixelShader> Resolve(const char* FileName);
	static std::string GenerateUID(const std::string& FileName);
	std::string GetUID() const noexcept override;
protected:
	std::string m_pass;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
};