#pragma once
#include"Bindable.h"
#include"renderer.h"
#include <io.h>
#include<string>
#include"model.h"

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(const char* tag, MODEL& model);
	void Bind()noexcept override;

	static std::shared_ptr<VertexBuffer> Resolve(const char* tag, MODEL& model);
	template<typename...Ignore>
	static std::string GenerateUID(const std::string& tag, Ignore&&...ignore)
	{
		return GenerateUID_(tag);
	}

	std::string GetUID() const noexcept override;
private:
	static std::string GenerateUID_(const std::string& tag);
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	std::string m_tag;
};

