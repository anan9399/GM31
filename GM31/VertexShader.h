#pragma once
#include"Bindable.h"
#include"renderer.h"
#include <io.h>
#include<string>

class VertexShader : public Bindable
{
public:
	VertexShader(const char* FileName);
	void Bind()noexcept override;
	const long int Getfsize() {
		return m_fsize;
	}
	const unsigned char* GetBuffer() {
		return m_buffer;
	}

	static std::shared_ptr<VertexShader> Resolve(const char* FileName);
	static std::string GenerateUID(const std::string& FileName);
	std::string GetUID() const noexcept override;

protected:
	std::string m_pass;
	long int m_fsize;
	unsigned char* m_buffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;

};


