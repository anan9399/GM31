#pragma once
#include<wrl.h>
#include<string>
#include<memory>
class Bindable
{
public:
	virtual void Bind() noexcept = 0;
	virtual ~Bindable() = default;
	virtual std::string GetUID() const noexcept
	{
		//assert(false);
		return "";
	}

protected:

};