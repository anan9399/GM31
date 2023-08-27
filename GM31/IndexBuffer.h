#pragma once
#include"Bindable.h"
#include"renderer.h"
#include <io.h>
#include<string>
#include"model.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer( const char* tag, MODEL& model);
	void Bind()noexcept override;

	static std::shared_ptr<IndexBuffer> Resolve(const char* tag,MODEL& model);
	template<typename...Ignore>
	static std::string GenerateUID(const std::string& tag, Ignore&&...ignore)
	{
		return GenerateUID_(tag);
	}

	std::string GetUID() const noexcept override;
private:
	static std::string GenerateUID_(const std::string& tag);
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	std::string m_tag;
};

