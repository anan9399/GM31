#pragma once
#include"Bindable.h"
#include"renderer.h"
#include <io.h>


class VertexShader : public Bindable
{
public:
	VertexShader(const char* FileName);
	void Bind()noexcept override;
	long int Getfsize() {
		return m_fsize;
	}
	unsigned char* GetBuffer() {
		return m_buffer;
	}
protected:
	long int m_fsize;
	unsigned char* m_buffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;

};


