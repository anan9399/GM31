#pragma once
#include "Bindable.h"
#include"main.h"
#include<wrl.h>
#include<memory>
#include<string>

class Surface;


class Texture : public Bindable
{
public:
	Texture(const std::string& path, UINT slot = 0);
	void Bind() noexcept override;

	static std::shared_ptr<Texture> Resolve(const std::string& path, UINT slot = 0);
	static std::string GenerateUID(const std::string& path, UINT slot = 0);
	std::string GetUID() const noexcept override;
private:
	unsigned int m_slot;
protected:
	std::string m_path;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTextureView;
};