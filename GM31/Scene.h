#pragma once
#include<memory>
#include<typeinfo>
#include<vector>
#include <list>
#include "GameObject.h"

class Scene {

protected:
	std::list<GameObject*> m_GameObjs[3];

public:
	
	virtual void Init() 
	{
	};
	virtual void UnInit()
	{
		for (int i = 0; i < 3; i++) {
			for (auto& g : m_GameObjs[i]) {
				g->Uninit();
			}
			m_GameObjs[i].clear();
		}
	};


	virtual void Update()
	{
		for (int i = 0; i < 3; i++) {
			for (auto& g : m_GameObjs[i]) {
				g->Update();

			}

			m_GameObjs[i].remove_if([](GameObject* object)
				{return object->Destory(); });
		}
	//m_GameObjs.erase(std::remove_if(m_GameObjs.begin(), m_GameObjs.end(),
	//					[](GameObject* object){return object->Destory(); }
	//				), m_GameObjs.end()
	//);

	};
	virtual void Draw()
	{
		for(int i = 0;i < 3; i++){
			for (auto& g : m_GameObjs[i]) {
				g->Draw();
			}
		}
	};


	template<typename T>
	T* AddGameObj(int layer) {
		T* component = new T();
		m_GameObjs[layer].push_back(component);
		component->Init();

		return static_cast<T*>(component);
	}

	template<typename T>
	T* GetGameObj() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObjs[i]) {
				if (typeid(*object) == typeid(T&))
				{
					return static_cast<T*>(object);
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetGameObjs() {
		std::vector<T*> objects;
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObjs[i]) {
				if (typeid(*object) == typeid(T&))
				{
					objects.push_back(static_cast<T*>(object));
				}
			}
		}

		return objects;
	}

};