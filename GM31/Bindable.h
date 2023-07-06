#pragma once
#include<wrl.h>

class Bindable
{
public:
	virtual void Bind() noexcept = 0;
	virtual ~Bindable() = default;
protected:

};