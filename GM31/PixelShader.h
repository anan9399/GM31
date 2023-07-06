#pragma once
#include "Bindable.h"
#include"renderer.h"
#include<io.h>

class PixelShader : public Bindable
{
public:
	PixelShader(const char* FileName);
	void Bind() noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
};