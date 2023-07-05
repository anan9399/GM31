#include "PixelShader.h"

PixelShader::PixelShader( const char* FileName)
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
