#pragma once
#include "Bindable.h"
#include "BindableCodex.h"
#include <memory>
#include <unordered_map>
#include <type_traits>

//  Singleton class
// TODO make a garbage collection 
// to loop all the shared_ptr check the useage 
class Codex
{
public:
	//paramater package
	//This paramater package can accept an unlimited number of different reference types.
	template<class T, typename...Params>
	static std::shared_ptr<T> Resolve(Params&&...p)
	{
		return Get().Resolve_<T>(std::forward<Params>(p)...);
	}
private:
	template<class T, typename...Params>
	std::shared_ptr<T> Resolve_(Params&&...p)
	{
		const auto key = T::GenerateUID(std::forward<Params>(p)...);
		const auto i = binds.find(key);
		if (i == binds.end())
		{
			auto bind = std::make_shared<T>(std::forward<Params>(p)...);
			binds[key] = bind;
			return bind;
		}
		else
		{
			return std::static_pointer_cast<T>(i->second);
		}
	}
	static Codex& Get()
	{
		static Codex codex;
		return codex;
	}
private:
	std::unordered_map<std::string, std::shared_ptr<Bindable>> binds;
};
