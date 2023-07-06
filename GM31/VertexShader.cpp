#include "VertexShader.h"
#include <typeinfo>
#include<d3dcompiler.h>
#include "BindableCodex.h"



VertexShader::VertexShader(const char* FileName)
	:
	m_pass(FileName)
{
	FILE* file;

	
	fopen_s(&file, FileName, "rb");
	assert(file);

	m_fsize = _filelength(_fileno(file));
	m_buffer = new unsigned char[m_fsize];
	fread(m_buffer, m_fsize, 1, file);
	fclose(file);

	Renderer::GetDevice()->CreateVertexShader(m_buffer, m_fsize, NULL, m_pVertexShader.ReleaseAndGetAddressOf());

}

void VertexShader::Bind() noexcept
{
	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
}

std::shared_ptr<VertexShader> VertexShader::Resolve(const char* FileName)
{
	return Codex::Resolve<VertexShader>(FileName);
}

std::string VertexShader::GenerateUID(const std::string& FileName)
{
	using namespace std::string_literals;
	return typeid(VertexShader).name() + "#"s + FileName;
}

std::string VertexShader::GetUID() const noexcept
{
	return GenerateUID(m_pass);
}