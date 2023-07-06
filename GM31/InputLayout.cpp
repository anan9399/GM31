#include "InputLayout.h"
#include "BindableCodex.h"


void InputLayout::Bind() noexcept
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
}

//std::shared_ptr<InputLayout> InputLayout::Resolve(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const std::string& name, VertexShader& vs)
//{
//	return Codex::Resolve<InputLayout>(layout, name,vs);
//}
//
//std::string InputLayout::GenerateUID(const std::string& FileName, VertexShader& vs)
//{
//	using namespace std::string_literals;
//	return typeid(InputLayout).name() + "#"s + FileName + vs.GetUID();
//}
//
//std::string InputLayout::GetUID() const noexcept
//{
//	return "layout";
//}