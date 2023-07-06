#include "PixelShader.h"
#include"BindableCodex.h"

PixelShader::PixelShader( const char* FileName)
	:
	m_pass(FileName)
{
	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Renderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, m_pPixelShader.ReleaseAndGetAddressOf());

	delete[] buffer;
}

void PixelShader::Bind() noexcept
{
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);
}


std::shared_ptr<PixelShader> PixelShader::Resolve(const char* FileName)
{
	return Codex::Resolve<PixelShader>(FileName);
}

std::string PixelShader::GenerateUID(const std::string& FileName)
{
	using namespace std::string_literals;
	return typeid(PixelShader).name() + "#"s + FileName;
}

std::string PixelShader::GetUID() const noexcept
{
	return GenerateUID(m_pass);
}