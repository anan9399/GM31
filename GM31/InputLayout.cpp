#include "InputLayout.h"



void InputLayout::Bind() noexcept
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
}
