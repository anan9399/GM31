#include "VertexShader.h"
#include <typeinfo>
#include<d3dcompiler.h>

VertexShader::VertexShader(const char* FileName)
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
